/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouillo <mpouillo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:47:49 by mpouillo          #+#    #+#             */
/*   Updated: 2025/12/15 21:15:28 by mpouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_memory_buffer(char const *memory, char const *buffer)
{
	char	*new_s;
	size_t	len_mem;
	size_t	len_buf;
	size_t	i;

	len_mem = protected_strlen(memory);
	len_buf = protected_strlen(buffer);
	new_s = malloc((len_mem + len_buf + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	i = -1;
	while (++i < len_mem)
		new_s[i] = memory[i];
	i = -1;
	while (++i < len_buf)
		new_s[len_mem + i] = buffer[i];
	new_s[len_mem + len_buf] = '\0';
	return (new_s);
}

size_t	protected_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*protected_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char			*new_str;
	const size_t	len = protected_strlen(s);
	size_t			i;

	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	i;
	size_t	len_s;

	if (!s || len == 0)
		return (NULL);
	len_s = protected_strlen(s);
	if (start >= len_s)
	{
		len = 0;
		start = len_s;
	}
	else if (start + len > len_s)
		len = len_s - start;
	new_s = malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] && start + i < len_s)
	{
		new_s[i] = s[start + i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
