/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 06:09:17 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/28 06:16:08 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_ray_direction(t_ray *ray, t_vector *vec, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = vec->dir_x + vec->plane_x * ray->camera_x;
	ray->ray_dir_y = vec->dir_y + vec->plane_y * ray->camera_x;
}

static void	init_ray_delta(t_ray *ray, t_vector *vec)
{
	ray->map_x = (int)vec->pos_x;
	ray->map_y = (int)vec->pos_y;
	ray->delta_dist_x = 1e30;
	ray->delta_dist_y = 1e30;
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

static void	init_step_x(t_ray *ray, t_vector *vec)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x
			= (vec->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x
			= (ray->map_x + 1.0 - vec->pos_x) * ray->delta_dist_x;
	}
}

static void	init_step_y(t_ray *ray, t_vector *vec)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y
			= (vec->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y
			= (ray->map_y + 1.0 - vec->pos_y) * ray->delta_dist_y;
	}
}

void	init_ray(t_ray *ray, t_vector *vec, int x)
{
	init_ray_direction(ray, vec, x);
	init_ray_delta(ray, vec);
	init_step_x(ray, vec);
	init_step_y(ray, vec);
}
