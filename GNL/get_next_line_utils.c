/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:15:47 by alfsanch          #+#    #+#             */
/*   Updated: 2024/11/06 17:15:51 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_buffer(char *buffer, char *temp)
{
	char	*new_buffer;

	if (!buffer)
		buffer = ft_strdup("");
	if (!buffer || !temp)
		return (NULL);
	new_buffer = ft_strjoin(buffer, temp);
	free(buffer);
	return (new_buffer);
}

char	*read_and_append(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = append_buffer(buffer, temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}


char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + (buffer[i] == '\n'));
	return (line);
}

char	*update_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_substr(buffer, i + 1, ft_strlen(buffer) - i - 1);
	free(buffer);
	return (new_buffer);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	newstr;
	char	*s3;

	i = 0;
	j = 0;
	newstr = ft_strlen(s1) + ft_strlen(s2);
	s3 = malloc(newstr +1);
	if (s3 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			src_len;

	i = 0;
	if (src == NULL)
		return (0);
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (i < size - 1 && i < src_len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		return (ft_strdup(""));
	}
	if (len > s_len)
		len = s_len;
	substr = (char *)malloc(len +  1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	while (*str)
	{
		if (*str == uc)
			return ((char *)str);
		str++;
	}
	if (uc == '\0')
		return ((char *)str);
	return (0);
}

void	*ft_calloc(size_t n, size_t size)
{
	char	*str;

	if (n <= 0 || size <= 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(n * size);
	if (!str)
		return (NULL);
	return (ft_memset(str, 0, n * size));
}