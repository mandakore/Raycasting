/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:38:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/29 14:24:17 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// static void	draw_debug_distance(t_game *game, t_ray *ray, int x)
// {
// 	int	color_value;
// 	int	color;
// 	int	y;

// 	color_value = 255 - (int)(ray->perp_wall_dist * 25);
// 	if (color_value < 0)
// 		color_value = 0;
// 	color = (color_value << 16) | (color_value << 8) | color_value;
// 	y = ray->draw_start;
// 	while (y < ray->draw_end)
// 	{
// 		put_pixel(x, y, color, game);
// 		y++;
// 	}
// }

static void	draw_debug_compass(t_game *game, t_ray *ray, int x)
{
	int	color;
	int	y;

	if (ray->side == 1) // Y軸面 (南北)
	{
		if (ray->ray_dir_y < 0)
			color = 0xFF0000; // 北 (Red)
		else
			color = 0x00FF00; // 南 (Green)
	}
	else // X軸面 (東西)
	{
		if (ray->ray_dir_x < 0)
			color = 0x0000FF; // 西 (Blue)
		else
			color = 0xFFFF00; // 東 (Yellow)
	}
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		put_pixel(x, y, color, game);
		y++;
	}
}

int	raycasting(t_game *game)
{
	t_ray		ray;
	t_vector	vec;
	int			x;

	move_player(game);
	clear_player(game);
	vec.pos_x = game->player.x / WALL;
	vec.pos_y = game->player.y / WALL;
	vec.dir_x = cos(game->player.dire);
	vec.dir_y = sin(game->player.dire);
	vec.plane_x = -vec.dir_y * 0.66;
	vec.plane_y = vec.dir_x * 0.66;
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, &vec, x);
		perform_dda(game, &ray);
		calc_wall_height(&ray);
		// draw_debug_distance(game, &ray, x);
		draw_debug_compass(game, &ray, x);
		x++;
	}
	create_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
