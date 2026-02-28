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

static void	draw_player(t_game *game)
{
	t_square	player_square;

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

void	create_map(t_game *game)
{
	draw_walls(game);
	draw_player(game);
}
