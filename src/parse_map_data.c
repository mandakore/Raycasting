/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:39:36 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/17 23:44:19 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	copy_map_data(t_map *map, char *src, size_t n)
{
	size_t	i;

	if (map == NULL || src == NULL)
		return (false);
	i = 0;
	while (src[i] != '\0' && i < map->x)
	{
		if (src[i] == '\n')
			src[i] = ' ';
		map->mapdata[n][i] = src[i];
		i++;
	}
	map->mapdata[n][map->x] = '\0';
	return (true);
}

static bool	get_user_entry(t_map *map)
{
	size_t	y;
	size_t	x;

	if (map == NULL)
		return (false);
	y = 0;
	while (y < map->y)
	{
		x = 0;
		while (x < map->x)
		{
			if (is_user(map->mapdata[y][x]) == true)
			{
				map->user_x = x;
				map->user_y = y;
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

static bool	is_wall_symbol(char c)
{
	if (c != ' ' || c != '1' || c != '0')
		return (false);
	return (true);
}

static bool	is_valid_map_line(t_map *map, char *line)
{
	static int	user;
	int			i;

	if (map == NULL || line == NULL)
		return (false);
	i = 0;
	while (line[i] != '\0')
	{
		if (is_wall_symbol(line[i]) == false && is_user(line[i]) == true)
				user++;
		if (user > 1)
			return (false);
		i++;
	}
	return (true);
}

bool	parse_map_data(t_map *map)
{
	char	*line;
	size_t	i;

	if (map == NULL)
		return (false);
	i = 0;
	while (i < map->y)
	{
		line = get_next_line(map->cubfd);
		if (line == NULL)
			break ;
		if (line[0] != '\n' && is_valid_map_line(map, line) != true)
			return (free(line), false);
		if (copy_map_data(map, line, i) != true)
			return (free(line), false);
		printf("%ld: %s\n", i, map->mapdata[i]);
		free(line);
		i++;
	}
	if (get_user_entry(map) != true)
		return (false);
	if (is_map_closed(map) != true)
		return (false);
	return (true);
}
