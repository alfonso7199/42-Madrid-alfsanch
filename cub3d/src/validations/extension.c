/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 19:27:15 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/10/31 15:16:46 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_bool	has_cub_extension(const char *path)
{
	const char	*dot;

	if (!path || !*path)
		return (FALSE);
	dot = ft_strrchr(path, '.');
	if (!dot || dot == path)
		return (FALSE);
	if (ft_strlen(dot) != 4)
		return (FALSE);
	if ((dot[1] == 'c' || dot[1] == 'C')
		&& (dot[2] == 'u' || dot[2] == 'U')
		&& (dot[3] == 'b' || dot[3] == 'B'))
		return (TRUE);
	return (FALSE);
}

t_bool	validate_map_extension(const char *path)
{
	if (!has_cub_extension(path))
	{
		ft_putendl_fd("Error: invalid file extension, expected '.cub'",
			STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}
