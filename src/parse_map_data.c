/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:39:36 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/13 02:26:14 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	is_wall_symbol(char c)
{
	if (c != ' ' || c != '1' || c != '0')
		return (false);
	return (true);
}

static bool	is_valid_map_line(t_map *map, char *line, int y)
{
	static int	user;
	int			i;

	if (map == NULL || line == NULL)
		return (false);
	i = 0;
	user = 0;
	while (line[i] != '\0')
	{
		if (is_wall_symbol(line[i]) != true)
		{
			if (is_user(line[i]) != true)
				return (false);
			else
			{
				map->user_x = i;
				map->user_y = y;
				user++;
			}
		}
		if (user > 1)
			return (false);
		i++;
	}
	return (true);
}

bool	parse_map_data(t_map *map)
{
	size_t	y;
	char	*line;

	y = 0;
	while (y < map->y)
	{
		line = get_next_line(map->cubfd);
		if (line == NULL)
			break ;
		if (is_valid_map_line(map, line, y) != true)
			return (free(line), false);
		map->mapdata[y] = line;
		y++;
	}
	if (is_map_closed(map) != true)
		return (false);
	return (true);
}
