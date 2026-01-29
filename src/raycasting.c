/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:38:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/29 16:22:47 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

// static unsigned int	apply_shading(unsigned int color, double distance)
// {
// 	double	shade_factor;
// 	int		r;
// 	int		g;
// 	int		b;

// 	shade_factor = 1.0 - (distance / 15.0);

// 	if (shade_factor < 0.0)
// 		shade_factor = 0.0;

// 	r = (color >> 16) & 0xFF;
// 	g = (color >> 8) & 0xFF;
// 	b = color & 0xFF;

// 	r = (int)(r * shade_factor);
// 	g = (int)(g * shade_factor);
// 	b = (int)(b * shade_factor);
// 	return ((r << 16) | (g << 8) | b);
// }

// static void	draw_debug_compass(t_game *game, t_ray *ray, int x)
// {
// 	int	color;
// 	int	y;

// 	if (ray->side == 1) // Y軸面 (南北)
// 	{
// 		if (ray->ray_dir_y < 0)
// 		{
// 			color = 0xFF0000; // 北 (Red)
// 			color = apply_shading(color, ray->perp_wall_dist);
// 		}	
// 		else
// 		{
// 			color = 0x00FF00; // 南 (Green)
// 			color = apply_shading(color, ray->perp_wall_dist);
// 		}
// 	}
// 	else // X軸面 (東西)
// 	{
// 		if (ray->ray_dir_x < 0)
// 		{
// 			color = 0x0000FF; // 西 (Blue)
// 			color = apply_shading(color, ray->perp_wall_dist);
// 		}
// 		else
// 		{
// 			color = 0xFFFF00; // 東 (Yellow)
// 			color = apply_shading(color, ray->perp_wall_dist);
// 		}
	
// 	}
// 	y = ray->draw_start;
// 	while (y < ray->draw_end)
// 	{
// 		put_pixel(x, y, color, game);
// 		y++;
// 	}
// }

static void	draw_texture(t_game *game, t_vector *vec, t_ray *ray, int x)
{
	t_img	*tex = &game->textures[ray->tex_num];
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;

	if (ray->side == 0) wall_x = vec->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else                wall_x = vec->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
		
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HIGHT / 2 + ray->line_height / 2) * step;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		int tex_y = (int)tex_pos & (tex->height - 1); 
		tex_pos += step;
		put_pixel(x, y, get_pixel_color(tex, tex_x, tex_y), game);
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
		// draw_debug_compass(game, &ray, x);
		draw_texture(game, &vec, &ray, x);
		x++;
	}
	create_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
