/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:09:25 by mpouillo          #+#    #+#             */
/*   Updated: 2025/12/15 11:05:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_memory_buffer(char const *memory, char const *buffer)
{
	char	*new_s;
	size_t	len_mem;
	size_t	len_buf;
	size_t	i;

	len_mem = ft_strlen(memory);
	len_buf = ft_strlen(buffer);
	new_s = malloc((len_mem + len_buf + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	while (memory && memory[i])
	{
		new_s[i] = memory[i];
		i++;
	}
	i = 0;
	while (buffer && buffer[i])
	{
		new_s[len_mem + i] = buffer[i];
		i++;
	}
	new_s[len_mem + len_buf] = '\0';
	return (new_s);
}

static void	append_buffer_to_memory(char **memory, char *buffer)
{
	char	*tmp;

	if (!buffer[0])
	{
		memory = NULL;
		return ;
	}
	tmp = join_memory_buffer(*memory, buffer);
	free(*memory);
	*memory = tmp;
}

static char	*extract_line_from_memory(char **memory)
{
	char		*next_lines;
	char		*current_line;
	size_t		len;

	len = 0;
	while (*memory && (*memory)[len] && (*memory)[len] != '\n')
		len++;
	if (*memory && (*memory)[len] == '\n')
		len++;
	next_lines = ft_substr(*memory, len, ft_strlen(*memory) - len);
	current_line = ft_substr(*memory, 0, len);
	free(*memory);
	*memory = next_lines;
	return (current_line);
}

char	*get_next_line(int fd)
{
	static char	*memory[FD_MAX];
	char		*buffer;
	ssize_t		sz;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= FD_MAX)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	sz = 1;
	while (sz && !ft_strchr(memory[fd], '\n'))
	{
		sz = read(fd, buffer, BUFFER_SIZE);
		if (sz < 0)
		{
			free(buffer);
			free(memory[fd]);
			memory[fd] = NULL;
			return (NULL);
		}
		buffer[sz] = '\0';
		append_buffer_to_memory(&memory[fd], buffer);
	}
	free(buffer);
	return (extract_line_from_memory(&memory[fd]));
}
