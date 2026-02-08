/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:26:21 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/04 19:40:01 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_line_len(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		i++;
	return (i);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

int	is_in_map(t_game *game, int x, int y)
{
	if (y < 0 || y >= get_map_height(game->map))
		return (0);
	if (x < 0 || x >= get_line_len(game->map[y]))
		return (0);
	return (1);
}

int	is_wall(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return (1);
	return (0);
}

void	draw_minimap_wall(t_game *game, int x, int y)
{
	t_square	square;

	square.x = MM_PLAYER_X + x * WALL;
	square.y = MM_PLAYER_Y + y * WALL;
	square.size = WALL;
	square.color = 0xFFFFFF;
	draw_square(game, square);
}
