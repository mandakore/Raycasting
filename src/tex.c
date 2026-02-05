/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:43:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/05 18:05:07 by atashiro         ###   ########.fr       */
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

static double	calc_wall_x(t_vector *vec, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = vec->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = vec->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
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

static void	draw_texture_column(t_game *game, t_img *tex, t_ray *ray, int x, unsigned int floor_color, unsigned int ceil_color)
{
	double			step;
	double			tex_pos;
	int				y;
	int				tex_y;
	unsigned int	color;

	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(x, y, ceil_color, game);
		y++;
	}
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos = tex_pos + step;
		color = get_pixel_color(tex, ray->tex_x, tex_y);
		color = apply_shading(color, ray->perp_wall_dist);
		put_pixel(x, y, color, game);
		y++;
	}
	y = ray->draw_end;
	while (y < HEIGHT)
	{
		put_pixel(x, y, floor_color, game);
		y++;
	}
}

void	draw_texture(t_game *game, t_vector *vec, t_ray *ray, int x, unsigned int floor_color, unsigned int ceil_color)
{
	t_img	*tex;
	double	wall_x;

	tex = &game->textures[ray->tex_num];
	wall_x = calc_wall_x(vec, ray);
	set_tex_x(tex, ray, wall_x);
	draw_texture_column(game, tex, ray, x, floor_color, ceil_color);
}
