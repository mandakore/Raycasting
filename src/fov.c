/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:29:06 by atashiro          #+#    #+#             */
/*   Updated: 2026/03/04 16:36:18 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	is_in_fov(double px, double py, double dir_x, double dir_y, double plane_x, double plane_y)
{
	double	left_x;
	double	left_y;
	double	right_x;
	double	right_y;
	double	cross_l;
	double	cross_r;

	left_x = dir_x - plane_x;
	left_y = dir_y - plane_y;
	right_x = dir_x + plane_x;
	right_y = dir_y + plane_y;
	cross_l = px * left_y - py * left_x;
	cross_r = px * right_y - py * right_x;
	if (cross_l >= 0 && cross_r <= 0)
		return (1);
	return (0);
}

void	draw_fov(t_game *game)
{
	int		px;
	int		py;
	int		center_x;
	int		center_y;
	double	dir_x;
	double	dir_y;
	int		radius;

	center_x = MM_PLAYER_X + MM_RAD * WALL + (WALL - 6) / 4;
	center_y = MM_PLAYER_Y + MM_RAD * WALL + (WALL - 6) / 4;
	dir_x = cos(game->player.dire);
	dir_y = sin(game->player.dire);
	radius = MM_RAD * WALL;
	py = -radius;
	while (py <= radius)
	{
		px = -radius;
		while (px <= radius)
		{
			if (px * px + py * py <= radius * radius && is_in_fov((double)px, (double)py, dir_x, dir_y, -dir_y * 0.66, dir_x * 0.66))
				blend_pixel(center_x + px, center_y + py, game);
			px++;
		}
		py++;
	}
}
