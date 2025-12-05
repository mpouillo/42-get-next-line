/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouillo <mpouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:09:25 by mpouillo          #+#    #+#             */
/*   Updated: 2025/12/05 13:52:01 by mpouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	move_buf_to_memory(char **memory, char *buf)
{
	char	*tmp;

	if (*memory)
	{
		tmp = ft_strjoin(*memory, buf);
		free(*memory);
		*memory = tmp;
	}
	else
		*memory = ft_strdup(buf);
	free(buf);
}

static char	*get_line_from_memory(char **memory, int sz)
{
	char		*next_lines;
	char		*current_line;
	int			len;

	len = 0;
	while ((*memory)[len] && (*memory)[len] != '\n')
		len++;
	if ((*memory)[len] == '\n')
		len += 1;
	if ((len > 1 && (*memory)[len - 1] == '\n') || sz < BUFFER_SIZE)
	{
		next_lines = ft_substr(*memory, len, sz - len);
		current_line = ft_substr(*memory, 0, len);
		free(*memory);
		*memory = next_lines;
		return (current_line);
	}
	return (NULL);
}


char	*get_next_line(int fd)
{
	static char	*memory;
	char		*buf;
	char		*line;
	int			sz;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	sz = 1;
	while (sz)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (NULL);
		sz = read(fd, buf, BUFFER_SIZE);
		move_buf_to_memory(&memory, buf);
		line = get_line_from_memory(&memory, sz);
		if (line)
			return (line);
	}
	return (NULL);
}
