/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:43:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/23 14:15:56 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static double	calc_wall_x(t_player *player, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = player->y / (double)WALL + \
ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x / (double)WALL + \
ray->perp_wall_dist * ray->ray_dir_x;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}

static void	set_tex_x(t_img *tex, t_ray *ray, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex->width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		tex_x = tex->width - tex_x - 1;
	ray->tex_x = tex_x;
}

void	draw_texture(t_game *game, t_ray *ray, int x, t_color colorcf)
{
	t_img	*tex;
	double	wall_x;

	tex = &game->textures[ray->tex_num];
	wall_x = calc_wall_x(&game->player, ray);
	set_tex_x(tex, ray, wall_x);
	draw_texture_column(game, ray, x, colorcf);
}
