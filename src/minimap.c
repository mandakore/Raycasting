/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:33:14 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/31 21:02:09 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

#define MINIMAP_RADIUS 5 // 半径
#define MINIMAP_OFFSET_X 20 // 表示位置 X
#define MINIMAP_OFFSET_Y 20 // 表示位置 Y
#define MM_COLOR_PLAYER 0xFF0000 // 赤
#define MM_COLOR_BG 0xFFFFFF // 背景

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
			put_pixel(square.x + j, square.y + i, square.color, game);
			j++;
		}
		i++;
	}
}

// static void	draw_wall_square(t_game *game, int x, int y)
// {
// 	t_square	square;

// 	square.x = x * WALL;
// 	square.y = y * WALL;
// 	square.size = WALL;
// 	square.color = 0xADFF2F;
// 	draw_square(game, square);
// }

// static void	draw_map(t_game *game)
// {
// 	char	**map;
// 	int		x;
// 	int		y;

// 	map = game->map;
// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			if (map[y][x] == '1')
// 				draw_wall_square(game, x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// }

static void	draw_player(t_game *game)
{
	t_square	player_square;
	player_square.x = MINIMAP_OFFSET_X + MINIMAP_RADIUS * WALL;
	player_square.y = MINIMAP_OFFSET_Y + MINIMAP_RADIUS * WALL;

	player_square.size = 6;
	player_square.x += (WALL - player_square.size) / 2;
	player_square.y += (WALL - player_square.size) / 2;
	player_square.color = MM_COLOR_PLAYER;
	draw_square(game, player_square);
	draw_square(game, player_square);
}

static void draw_minimap_bg()
{
	t_square bg;
	int size_px = (MINIMAP_RADIUS * 2 + 1) * WALL;

	bg.x = MINIMAP_OFFSET_X;
	bg.y = MINIMAP_OFFSET_Y;
	bg.size = size_px;
}

void	create_map(t_game *game)
{
	// draw_map(game);
	draw_minimap_bg();
	draw_player(game);
}
