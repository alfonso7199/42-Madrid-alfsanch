/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzamolo- <rzamolo-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:21:10 by rzamolo-          #+#    #+#             */
/*   Updated: 2025/11/20 12:36:18 by rzamolo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_mlx_settings(void)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, TRUE);
	mlx_set_setting(MLX_FULLSCREEN, FALSE);
	mlx_set_setting(MLX_MAXIMIZED, FALSE);
	mlx_set_setting(MLX_DECORATED, TRUE);
}

uint32_t	darker_color(uint32_t color, float factor)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	if (factor < 0)
		factor = 0;
	if (factor > 1)
		factor = 1;
	r *= (1.0f - factor);
	g *= (1.0f - factor);
	b *= (1.0f - factor);
	return (r << 24 | g << 16 | b << 8 | a);
}
