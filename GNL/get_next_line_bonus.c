/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:21:55 by alfsanch          #+#    #+#             */
/*   Updated: 2024/11/18 17:21:58 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

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

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_append(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}

/*
int main (int argc, char **argv)
{
	int fd;
	char *line;
	int i;


	if (argc < 2)
	{
		printf("No has passado suficientes argumentos\n");
		return 1;
	}
	++argv;
	while (*argv)
	{
		fd = open(*argv, O_RDONLY);
		i = 0;
		while ((line = get_next_line(fd)))
		{
			printf("%i, line: %s", i, line);
			free(line);
			i++;
		}
		close(fd);
		++argv;
	}
}
*/
