/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:11:35 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:37:55 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_append_line(char **old, char *new_line)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (old)
		while (old[len])
			len++;
	new = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i++] = ft_strdup(new_line);
	new[i] = NULL;
	if (old)
		ft_free_split(old);
	return (new);
}
