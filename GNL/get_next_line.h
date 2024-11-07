/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:15:14 by alfsanch          #+#    #+#             */
/*   Updated: 2024/11/06 17:15:17 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_and_append(int fd, char *buffer);
char	*append_buffer(char *buffer, char *temp);
char	*extract_line(char *buffer);
char	*update_buffer(char *buffer);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
void	*ft_calloc(size_t count, size_t size);

#endif