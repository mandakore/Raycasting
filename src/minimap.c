/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:33:14 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/27 23:44:32 by atashiro         ###   ########.fr       */
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

void	create_map(t_game *game)
{
	char	**map = game->map;
	int		color = 0xADFF2F;
	t_square	square;

	int x;
	int y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
			{
				square.x = x * WALL;
				square.y = y * WALL;
				square.size = WALL;
				square.color = color;
				draw_square(game, square);
			}
			x++;
		}
		y++;
	}
	t_square player_square;
	t_player	*player = &game->player;

	player_square.x = (int)player->x;
	player_square.y = (int)player->y;
	player_square.size = 10;
	player_square.color = 0xFFFFFF;
	draw_square(game, player_square);
}
