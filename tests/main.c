#include "../get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define RED		"\033[0;31m"
#define YELLOW	"\033[0;33m"
#define BLUE	"\033[0;34m"
#define RESET	"\033[0m"

#define PRINT_LINE printf("%s(%i: %2i)%s -> %s", BLUE, fd, line, RESET, str)

int g_malloc_fail_counter = 0;
int g_malloc_fail_target = 0;
int g_malloc_fail_active = 0;

void	print_line(char *str, int fd, int line)
{
	if (str && str[strlen(str) - 1] == '\n')
	{
		str[strlen(str) - 1] = '\0';
		PRINT_LINE;
		printf(RED"\\n"RESET);
	}
	else if (str && str[strlen(str) - 1] != '\n')
	{
		PRINT_LINE;
		printf(RED"\\0"RESET);
	}
	else 
		PRINT_LINE;
	printf("\n");
}

void	test_multiple_fd(void)
{
	printf("Testing multiple fds:\n");
	int fd1 = open("tests/files/testfd1.txt", O_RDONLY);
	int fd2 = open("tests/files/testfd2.txt", O_RDONLY);
	int fd3 = open("tests/files/testfd3.txt", O_RDONLY);
	char *str1 = malloc(1);
	char *str2 = malloc(1);
	char *str3 = malloc(1);
	printf(YELLOW"%s (%i):\n"RESET, "tests/files/testfd1.txt", fd1);
	printf(YELLOW"%s (%i):\n"RESET, "tests/files/testfd2.txt", fd2);
	printf(YELLOW"%s (%i):\n"RESET, "tests/files/testfd3.txt", fd3);
	int i = 0;
	while (str1 || str2 || str3)
	{
		free(str1);
		free(str2);
		free(str3);
		str1 = get_next_line(fd1);
		str2 = get_next_line(fd2);
		str3 = get_next_line(fd3);
		print_line(str1, fd1, i);
		print_line(str2, fd2, i);
		print_line(str3, fd3, i);
		i++;
	}
	free(str1);
	free(str2);
	free(str3);
	close(fd1);
	close(fd2);
	close(fd3);
}

void	test_single_fd(char *filename)
{
	int fd = open(filename, O_RDONLY);
	char *str = malloc(1);
	printf(YELLOW"%s (%i):\n"RESET, filename, fd);
	int i = 0;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		print_line(str, fd, i);
		i++;
	}
	free(str);
	close(fd);
}

void	*test_malloc(size_t size)
{
	if (g_malloc_fail_active)
	{
		if (g_malloc_fail_counter == g_malloc_fail_target)
		{
			g_malloc_fail_counter++;
			return (NULL);
		}
		g_malloc_fail_counter++;
	}
	return (realloc(NULL, size));
}

void	run_malloc_tests(char *filename)
{
	int		fd;
	char	*str;

	printf("Malloc protection check... (see Valgrind output)\n");
	g_malloc_fail_active = 1;
	g_malloc_fail_counter = 0;
	for (int i = 0; i < 10; i++)
	{
		g_malloc_fail_target = i;
		fd = open(filename, O_RDONLY);
		str = get_next_line(fd);
		free(str);
	}
	g_malloc_fail_active = 0;
	while ((str = get_next_line(fd)))
		free(str);
	close(fd);
}

void	run_read_error_tests(char *filename)
{
	char *str;

	printf("Read protection check... (see Valgrind output)");
	int fd = open(filename, O_RDONLY);
	str = get_next_line(fd);
	free(str);
	close(fd);
	while ((str = get_next_line(fd)))
		free(str);
	close(fd);
}

void	print_sep(void)
{
	printf("\n-------------------------------------------------------\n");
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (-1);
	char *bonus = "";
	argv++;
	if (strcmp(*argv, "--bonus") == 0)
	{
		argc--;
		argv++;
		bonus = "(Bonus check ON)";
	}
	printf("Running tests on %i files... %s", --argc, bonus);
	print_sep();
	while (*argv)
	{
		test_single_fd(*argv);
		printf("\n\n");
		run_malloc_tests(*argv);
		run_read_error_tests(*argv);
		print_sep();
		argv++;
	}
	if (bonus[0])
	{
		test_multiple_fd();
		print_sep();
	}
	return (0);
}