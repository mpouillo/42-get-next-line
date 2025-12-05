/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouillo <mpouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:09:25 by mpouillo          #+#    #+#             */
/*   Updated: 2025/12/05 10:16:14 by mpouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*buf;
	int			sz;
	int			len;
	char		*tmp;
	char		*tmp2;

	sz = 1;
	len = 0;
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (sz)
	{
		sz = read(fd, buf, BUFFER_SIZE);
		if (memory)
		{
			sz += ft_strlen(memory);
			tmp = ft_strjoin(memory, buf);
			free(memory);
			memory = tmp;
		}
		else
			memory = ft_strdup(buf);
		while (len < sz && memory[len] != '\n')
			len++;
		if (memory[len] == '\n')
			len += 1;
		if (len > 1 && memory[len - 1] == '\n')
		{
			tmp = ft_substr(memory, len, sz - len);
			tmp2 = ft_substr(memory, 0, len);
			free(memory);
			memory = tmp;
			free(buf);
			return (tmp2);
		}
	}
	free(buf);
	if (memory[0] == '\0')
	{
		free(memory);
		memory = NULL;
		return (NULL);
	}
	return (memory);
}

/*
#include "get_next_line.h"

static char	*handle_read(char **memory, char *buf, int *sz)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	if (!memory)
		memory = ft_strdup(buf);
	else
	{
		memory = strjoinfree(memory, buf);
		*sz += ft_strlen(memory);
	}
	len = 0;
	while (len < sz && *memory[len] != '\n')
		len++;
	len += (*memory[len] == '\n');
	if (len > 1 && *memory[len - 1] == '\n')
	{
		tmp = ft_substr(*memory, len, sz - len);
		tmp2 = ft_substr(*memory, 0, len);
		free(*memory);
		*memory = tmp;
		return (tmp2);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*memory;
	char		*buf;
	char		*line;
	int			len;
	int			sz;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	sz = 1;
	while (sz)
	{
		sz = read(fd, buf, BUFFER_SIZE);
		line = handle_read(&memory, buf, &sz);
		if (!line)
			return (line);
	}
	if (EMPTY_MEMORY)
	{
		free(memory);
		memory = NULL;
		return (NULL);
	}
	return (line);
}
*/