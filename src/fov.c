/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:29:06 by atashiro          #+#    #+#             */
/*   Updated: 2026/03/07 12:52:02 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	is_in_fov(double x, double y, double *dir, double *pl)
{
	double	left_x;
	double	left_y;
	double	right_x;
	double	right_y;

	left_x = dir[0] - pl[0];
	left_y = dir[1] - pl[1];
	right_x = dir[0] + pl[0];
	right_y = dir[1] + pl[1];
	if (x * left_y - y * left_x <= 0 && x * right_y - y * right_x >= 0)
		return (1);
	return (0);
}

static void	render_fov_pixels(t_game *game, double *dir, double *pl, int *c)
{
	int	x;
	int	y;
	int	r;

	r = MM_RAD * WALL;
	y = -r - 1;
	while (++y <= r)
	{
		x = -r - 1;
		while (++x <= r)
		{
			if (x * x + y * y <= r * r && is_in_fov(x, y, dir, pl))
				blend_pixel(c[0] + x, c[1] + y, game);
		}
	}
}

void	draw_fov(t_game *game)
{
	double	dir[2];
	double	pl[2];
	int		c[2];

	c[0] = MM_PLAYER_X + MM_RAD * WALL - (WALL - 6) / 4;
	c[1] = MM_PLAYER_Y + MM_RAD * WALL - (WALL - 6) / 4;
	dir[0] = cos(game->player.dire);
	dir[1] = sin(game->player.dire);
	pl[0] = -dir[1] * 0.66;
	pl[1] = dir[0] * 0.66;
	render_fov_pixels(game, dir, pl, c);
}
