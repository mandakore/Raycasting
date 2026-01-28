/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcurate_wall_height.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 06:09:11 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/28 06:13:11 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calc_wall_height(t_ray *ray)
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
