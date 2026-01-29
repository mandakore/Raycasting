/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:38:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/29 15:31:28 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static unsigned int	apply_shading(unsigned int color, double distance)
{
	double	shade_factor;
	int		r;
	int		g;
	int		b;

	shade_factor = 1.0 - (distance / 15.0);

	if (shade_factor < 0.0)
		shade_factor = 0.0;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;

	r = (int)(r * shade_factor);
	g = (int)(g * shade_factor);
	b = (int)(b * shade_factor);
	return ((r << 16) | (g << 8) | b);
}

static void	draw_debug_compass(t_game *game, t_ray *ray, int x)
{
	int	color;
	int	y;

	if (ray->side == 1) // Y軸面 (南北)
	{
		if (ray->ray_dir_y < 0)
		{
			color = 0xFF0000; // 北 (Red)
			color = apply_shading(color, ray->perp_wall_dist);
		}	
		else
		{
			color = 0x00FF00; // 南 (Green)
			color = apply_shading(color, ray->perp_wall_dist);
		}
	}
	else // X軸面 (東西)
	{
		if (ray->ray_dir_x < 0)
		{
			color = 0x0000FF; // 西 (Blue)
			color = apply_shading(color, ray->perp_wall_dist);
		}
		else
		{
			color = 0xFFFF00; // 東 (Yellow)
			color = apply_shading(color, ray->perp_wall_dist);
		}
	
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
