/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:33:14 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/28 17:55:02 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

#define MM_FOV_COLOR_R 0x00
#define MM_FOV_COLOR_G 0xCC
#define MM_FOV_COLOR_B 0x44
#define MM_FOV_ALPHA 0.30

static void draw_player(t_game *game) 
{
	t_square player_square;

	player_square.x = MM_PLAYER_X + MM_RAD * WALL;
	player_square.y = MM_PLAYER_Y + MM_RAD * WALL;
	player_square.size = 6;
	player_square.x -= (WALL - player_square.size) / 4;
	player_square.y -= (WALL - player_square.size) / 4;
	player_square.color = MM_PLAYER_COLOR;
	draw_square(game, player_square);
}

void	draw_minimap_floor(t_game *game, int x, int y)
{
	t_square	square;
	int			offset_x;
	int			offset_y;

	offset_x = (int)game->player.x % WALL;
	offset_y = (int)game->player.y % WALL;
	square.x = MM_PLAYER_X + x * WALL - offset_x;
	square.y = MM_PLAYER_Y + y * WALL - offset_y;
	square.size = WALL;
	square.color = MM_FLOOR_COLOR;
	draw_square(game, square);
}

static void	draw_walls(t_game *game)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;

	player_x = (int)(game->player.x) / WALL;
	player_y = (int)(game->player.y) / WALL;
	y = -MM_RAD;
	while (y <= MM_RAD)
	{
	x = -MM_RAD;
		while (x <= MM_RAD)
		{
			if (is_in_map(game, player_x + x, player_y + y))
			{
		if (is_wall(game, player_x + x, player_y + y))
			draw_minimap_wall(game, x + MM_RAD, y + MM_RAD);
		else
			draw_minimap_floor(game, x + MM_RAD, y + MM_RAD);
		}
		x++;
	}
	y++;
	}
}

void	draw_square(t_game *game, t_square square)
{
	int	i;
	int	j;

	i = 0;
	while (i < square.size)
	{
		j = 0;
		while (j < square.size)
		{
			if (i == 0 || i == square.size - 1
				|| j == 0 || j == square.size - 1)
			put_pixel(square.x + j, square.y + i, MM_WALL_COLOR, game);
			else
			put_pixel(square.x + j, square.y + i, square.color, game);
			j++;
		}
		i++;
	}
}

static void blend_pixel(int x, int y, t_game *game) 
{
	int idx;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
	return;
	idx = y * game->line_size + x * game->bit / 8;
	b = (unsigned char)game->data[idx];
	g = (unsigned char)game->data[idx + 1];
	r = (unsigned char)game->data[idx + 2];
	b = (unsigned int)(b * (1.0 - MM_FOV_ALPHA) + MM_FOV_COLOR_B * MM_FOV_ALPHA);
	g = (unsigned int)(g * (1.0 - MM_FOV_ALPHA) + MM_FOV_COLOR_G * MM_FOV_ALPHA);
	r = (unsigned int)(r * (1.0 - MM_FOV_ALPHA) + MM_FOV_COLOR_R * MM_FOV_ALPHA);
	game->data[idx] = b & 0xFF;
	game->data[idx + 1] = g & 0xFF;
	game->data[idx + 2] = r & 0xFF;
}

static int is_in_fov(double px, double py, double dir_x, double dir_y,
                     double plane_x, double plane_y)
{
	double left_x;
	double left_y;
	double right_x;
	double right_y;
	double cross_l;
	double cross_r;

	left_x = dir_x - plane_x;
	left_y = dir_y - plane_y;
	right_x = dir_x + plane_x;
	right_y = dir_y + plane_y;
	cross_l = px * left_y - py * left_x;
	cross_r = px * right_y - py * right_x;
	if (cross_l >= 0 && cross_r <= 0)
	return (1);
	return (0);
}

static void draw_fov(t_game *game)
{
	int px;
	int py;
	int center_x;
	int center_y;
	double dir_x;
	double dir_y;
	int radius;

	center_x = MM_PLAYER_X + MM_RAD * WALL + (WALL - 6) / 4;
	center_y = MM_PLAYER_Y + MM_RAD * WALL + (WALL - 6) / 4;
	dir_x = cos(game->player.dire);
	dir_y = sin(game->player.dire);
	radius = MM_RAD * WALL;
	py = -radius;
	while (py <= radius) 
	{
	px = -radius;
	while (px <= radius) 
	{
		if (px * px + py * py <= radius * radius &&
			is_in_fov((double)px, (double)py, dir_x, dir_y, -dir_y * 0.66,
					dir_x * 0.66))
		blend_pixel(center_x + px, center_y + py, game);
		px++;
	}
		py++;
	}
}

void create_map(t_game *game) 
{
	draw_walls(game);
	draw_fov(game);
	draw_player(game);
}
