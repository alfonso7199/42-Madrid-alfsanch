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

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return NULL;
    buffer = read_and_append(fd, buffer);
    if (!buffer)
        return NULL;
    line = extract_line(buffer);
    buffer = update_buffer(buffer);
    return line;
}