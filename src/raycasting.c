/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:38:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/28 04:24:17 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_ray(t_ray *ray, t_vector *vec, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = vec->dir_x + vec->plane_x * ray->camera_x;
	ray->ray_dir_y = vec->dir_y + vec->plane_y * ray->camera_x;
	ray->map_x = (int)vec->pos_x;
	ray->map_y = (int)vec->pos_y;
	ray->delta_dist_x = 1e30;
	ray->delta_dist_y = 1e30;
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (vec->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - vec->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (vec->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - vec->pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, t_ray *ray)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			hit = true;
	}
}

static void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist == 0)
		ray->perp_wall_dist = 0.01;
	ray->line_height = (int)(HIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HIGHT / 2;
	if (ray->draw_end >= HIGHT)
		ray->draw_end = HIGHT - 1;
}

static void	draw_debug_distance(t_game *game, t_ray *ray, int x)
{
	int	color_value;
	int	color;
	int	y;


	color_value = 255 - (int)(ray->perp_wall_dist * 25);
	if (color_value < 0) color_value = 0;

	color = 0xFF0000;

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
		draw_debug_distance(game, &ray, x);
		x++;
	}
	create_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
