/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:33:14 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/23 14:56:42 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
			if (is_in_map(game, player_x + x, player_y + y)
				&& is_wall(game, player_x + x, player_y + y))
			{
				draw_minimap_wall(game, x + MM_RAD, y + MM_RAD);
			}
			x++;
		}
		y++;
	}
}

void	create_map(t_game *game)
{
	draw_walls(game);
	draw_player(game);
}
