/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouillo <mpouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:09:25 by mpouillo          #+#    #+#             */
/*   Updated: 2025/12/17 07:48:28 by mpouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*handle_error(char **memory, char *buffer)
{
	free(buffer);
	free(*memory);
	*memory = NULL;
	return (NULL);
}

static int	append_buffer_to_memory(char **memory, char *buffer)
{
	char	*tmp;

	tmp = join_memory_buffer(*memory, buffer);
	if (!tmp)
	{
		free(*memory);
		*memory = NULL;
		return (ERROR);
	}
	free(*memory);
	*memory = tmp;
	return (SUCCESS);
}

static char	*extract_line_from_memory(char **memory)
{
	char		*next_lines;
	char		*current_line;
	size_t		len;

	if (!*memory || !**memory)
		return (handle_error(memory, NULL));
	len = 0;
	while ((*memory)[len] && (*memory)[len] != '\n')
		len++;
	if ((*memory)[len] == '\n')
		len++;
	current_line = ft_substr(*memory, 0, len);
	next_lines = ft_substr(*memory, len, protected_strlen(*memory) - len);
	free(*memory);
	*memory = next_lines;
	if (!current_line || !next_lines)
	{
		free(current_line);
		free(*memory);
		*memory = NULL;
		return (NULL);
	}
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
		return (handle_error(&memory[fd], buffer));
	sz = 1;
	while (sz && !protected_strchr(memory[fd], '\n'))
	{
		sz = read(fd, buffer, BUFFER_SIZE);
		if (sz == -1)
			return (handle_error(&memory[fd], buffer));
		buffer[sz] = '\0';
		if (sz > 0 && append_buffer_to_memory(&memory[fd], buffer) == ERROR)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (extract_line_from_memory(&memory[fd]));
}
