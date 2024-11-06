/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfsanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:14:58 by alfsanch          #+#    #+#             */
/*   Updated: 2024/11/06 17:15:04 by alfsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buffer)
{
    char	*line;
    char	*newline_pos;
    size_t len = newline_pos ? newline_pos - *buffer + 1 : ft_strlen(*buffer);

	*newline_pos = ft_strchr(*buffer, '\n');
    line = malloc(len + 1);
    if (!line)
        return NULL;

    for (size_t i = 0; i < len; i++)
        line[i] = (*buffer)[i];
    line[len] = '\0';

    if (newline_pos) {
        char *temp = ft_strjoin(newline_pos + 1, ""); 
        free(*buffer);
        *buffer = temp;
    } else {
        free(*buffer);
        *buffer = NULL;
    }
    return line;
}

static int read_to_buffer(int fd, char **buffer) {
    char *temp_buffer = malloc(BUFFER_SIZE + 1);
    if (!temp_buffer)
        return -1;

    int bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        temp_buffer[bytes_read] = '\0';
        *buffer = ft_strjoin(*buffer, temp_buffer);
    }
    free(temp_buffer);
    return bytes_read;
}

char *get_next_line(int fd) {
    static char *buffer = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    int bytes_read = 1;
    while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
        bytes_read = read_to_buffer(fd, &buffer);

    if (bytes_read < 0 || (bytes_read == 0 && !buffer))
        return NULL;

    return extract_line(&buffer);
}
