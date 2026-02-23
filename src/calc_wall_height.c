/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_height.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 06:09:11 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/23 14:13:02 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	calc_perp_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist == 0)
		ray->perp_wall_dist = 0.01;
}

static void	calc_draw_range(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	set_tex_num(t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->ray_dir_y < 0)
			ray->tex_num = 0;
		else
			ray->tex_num = 1;
	}
	else
	{
		if (ray->ray_dir_x < 0)
			ray->tex_num = 2;
		else
			ray->tex_num = 3;
	}
}

void	calc_wall_height(t_ray *ray)
{
	calc_perp_wall_dist(ray);
	calc_draw_range(ray);
	set_tex_num(ray);
}
