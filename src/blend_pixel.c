/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:35:46 by atashiro          #+#    #+#             */
/*   Updated: 2026/03/04 17:04:26 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	blend_pixel(int x, int y, t_game *game)
{
	int				idx;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	idx = y * game->line_size + x * game->bit / 8;
	b = (unsigned char)game->data[idx];
	g = (unsigned char)game->data[idx + 1];
	r = (unsigned char)game->data[idx + 2];
	b = (unsigned int)(b * (1.0 - MM_FOV_D) + MM_FOV_COLOR_B * MM_FOV_D);
	g = (unsigned int)(g * (1.0 - MM_FOV_D) + MM_FOV_COLOR_G * MM_FOV_D);
	r = (unsigned int)(r * (1.0 - MM_FOV_D) + MM_FOV_COLOR_R * MM_FOV_D);
	game->data[idx] = b & 0xFF;
	game->data[idx + 1] = g & 0xFF;
	game->data[idx + 2] = r & 0xFF;
}
