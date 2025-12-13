#include "../get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

#define RED		"\033[0;31m"
#define GREEN	"\033[0;32m"
#define RESET	"\033[0m"

void run_gnl_tests(int argc, char **argv)
{
	char	*str;
	int		fd1;
	int		fd2;
	int		fd3;
	int		i;

	i = 0;
	if (argc == 2)
	{
		fd1 = open(argv[1], O_RDONLY);
		str = malloc(1);
		__builtin_printf("%s (%i):\n", argv[1], fd1);
		while (str)
		{
			free(str);
			str = get_next_line(fd1);
			__builtin_printf("(%i: %2i) -> %s", fd1, i, str);
			i++;
		}
		close(fd1);
	}
	if (argc == 3)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		str = malloc(1);
		__builtin_printf("%s (%i):\n", argv[1], fd1);
		__builtin_printf("%s (%i):\n", argv[2], fd2);
		while (str)
		{
			free(str);
			str = get_next_line(fd1);
			__builtin_printf("(%i: %2i) -> %s", fd1, i, str);
			free(str);
			str = get_next_line(fd2);
			__builtin_printf("(%i: %2i) -> %s", fd2, i, str);
			i++;
		}
		close(fd1);
		close(fd2);
	}
	if (argc > 3)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		fd3 = open(argv[3], O_RDONLY);
		str = malloc(1);
		__builtin_printf("%s (%i):\n", argv[1], fd1);
		__builtin_printf("%s (%i):\n", argv[2], fd2);
		__builtin_printf("%s (%i):\n", argv[3], fd3);
		while (str)
		{
			free(str);
			str = get_next_line(fd1);
			__builtin_printf("(%i: %2i) -> %s", fd1, i, str);
			free(str);
			str = get_next_line(fd2);
			__builtin_printf("(%i: %2i) -> %s", fd2, i, str);
			free(str);
			str = get_next_line(fd3);
			__builtin_printf("(%i: %2i) -> %s", fd3, i, str);
			i++;
		}
		close(fd1);
		close(fd2);
		close(fd3);
	}
}

int g_malloc_fail_counter = 0;
int g_malloc_fail_target = 0;
int g_malloc_fail_active = 0;

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

	__builtin_printf("\nMalloc protection check... (see Valgrind output)\n");
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

	__builtin_printf("\nRead protection check... (see Valgrind output)\n\n");
	int fd = open(filename, O_RDONLY);
	str = get_next_line(fd);
	free(str);
	close(fd);
	while ((str = get_next_line(fd)))
		free(str);
	close(fd);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (-1);
	__builtin_printf("\n-------------------------------------------------------\n");
	run_gnl_tests(argc, argv);
	__builtin_printf("\n-------------------------------------------------------\n");
	run_malloc_tests(argv[1]);
	run_read_error_tests(argv[1]);
	return (0);
}