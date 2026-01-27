/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:38:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/28 04:08:30 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}	t_ray;

typedef struct s_vector
{
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
}	t_vector;

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

static void	calc_wall_height(t_vector *vec, t_ray *ray)
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
	(void)vec;
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
		calc_wall_height(&vec, &ray);
		x++;
	}
	create_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
