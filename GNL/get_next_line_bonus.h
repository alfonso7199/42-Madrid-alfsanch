/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:22:36 by alfsanch          #+#    #+#             */
/*   Updated: 2024/11/18 17:22:38 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_and_append(int fd, char *buffer);
char	*append_buffer(char *buffer, char *temp);
char	*extract_line(char *buffer);
char	*update_buffer(char *buffer);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int c);

#endif
