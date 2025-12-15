/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouillo <mpouillo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:09:52 by mpouillo          #+#    #+#             */
/*   Updated: 2025/12/15 21:23:31 by mpouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# ifndef ERROR
#  define ERROR -1
# endif

# ifndef SUCCESS
#  define SUCCESS 1
# endif

//		get_net_line_bonus.c
char	*get_next_line(int fd);

//		get_next_line_utils_bonus.c
char	*join_memory_buffer(char const *memory, char const *buffer);
size_t	protected_strlen(const char *str);
char	*protected_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
