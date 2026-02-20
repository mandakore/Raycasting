/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:38:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/19 17:47:29 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init_camera(t_game *game, t_vector *vec)
{
	vec->pos_x = game->player.x / WALL;
	vec->pos_y = game->player.y / WALL;
	vec->dir_x = cos(game->player.dire);
	vec->dir_y = sin(game->player.dire);
	vec->plane_x = -vec->dir_y * 0.66;
	vec->plane_y = vec->dir_x * 0.66;
}

static t_color	init_color_cf(void)
{
	t_color	color;

	color.floor = 0x000000;
	color.ceil = 0x000000;
	return (color);
}

static void	cast_single_ray(t_game *game, t_vector *vec, t_color color, int x)
{
	t_ray	ray;

	init_ray(&ray, vec, x);
	perform_dda(game, &ray);
	calc_wall_height(&ray);
	draw_texture(game, &ray, x, color);
}

static void	finalize_render(t_game *game)
{
	create_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int	raycasting(t_game *game)
{
	t_vector	vec;
	t_color		colorcf;
	int			x;

	move_player(game);
	init_camera(game, &vec);
	colorcf = init_color_cf();
	x = 0;
	while (x < WIDTH)
	{
		cast_single_ray(game, &vec, colorcf, x);
		x++;
	}
	finalize_render(game);
	return (0);
}
