/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:43:04 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/07 14:44:59 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_texture_step(t_ray *ray, t_img *tex,
		double *step, double *tex_pos)
{
	*step = (double)tex->height / ray->line_height;
	*tex_pos = (ray->draw_start - HEIGHT / 2
			+ ray->line_height / 2) * (*step);
}

static void	draw_ceil(t_game *game, int x, int draw_start, unsigned int color)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel(x, y, color, game);
		y++;
	}
}

static void	draw_wall_texture( t_game *game, t_ray *ray, t_img *tex, int x)
{
	double			step;
	double			tex_pos;
	int				y;
	int				tex_y;
	unsigned int	color;

	init_texture_step(ray, tex, &step, &tex_pos);
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
}

static void	draw_floor(
	t_game *game,
	int x,
	int draw_end,
	unsigned int color
)
{
	int	y;

	y = draw_end;
	while (y < HEIGHT)
	{
		put_pixel(x, y, color, game);
		y++;
	}
}

void	draw_texture_column( t_game *game, t_ray *ray, int x, t_color c)
{
	t_img	*tex;

	tex = &game->textures[ray->tex_num];
	draw_ceil(game, x, ray->draw_start, c.ceil);
	draw_wall_texture(game, ray, tex, x);
	draw_floor(game, x, ray->draw_end, c.floor);
}