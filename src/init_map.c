/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 01:31:45 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/03/07 13:02:33 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	allocate_square_map(t_map *map)
{
	size_t	i;

	if (map == NULL)
		return (false);
	map->mapdata = (char **)ft_calloc(map->y + 1, sizeof(char *));
	if (map->mapdata == NULL)
		return (perror("Error\n"), false);
	i = 0;
	while (i < map->y)
	{
		map->mapdata[i] = (char *)ft_calloc(map->x + 1, sizeof(char));
		if (map->mapdata[i] == NULL)
			return (perror("Error\n"), free_sheet(map->mapdata), false);
		map->mapdata[i] = (char *)ft_memset(map->mapdata[i], ' ', map->x);
		i++;
	}
	return (true);
}

static size_t	get_map_width(char *line, size_t current)
{
	size_t	len;

	if (line == NULL)
		return (0);
	len = ft_strlen(line) + 1;
	if (current < len)
		return (len);
	else
		return (current);
}

static bool	count_config_line(t_map *map, int fd)
{
	char	*line;
	size_t	conf;

	if (map == NULL)
		return (false);
	conf = 0;
	while (conf < 6)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return (print_lack_of_config(), false);
		if (is_config_line(line[0]) == true)
			conf++;
		map->config_line++;
		free(line);
	}
	return (true);
}

static bool	get_map_size(t_map *map, int fd)
{
	char	*line;

	if (map == NULL)
		return (false);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		map->x = get_map_width(line, map->x);
		map->y++;
		free(line);
	}
	if (map->x == 0 || map->y == 0)
		return (print_nomap_error(), false);
	else if (map->x >= 512 || map->y >= 512)
		return (print_too_big_map(), false);
	return (true);
}

t_map	*init_map(int argc, char **argv)
{
	t_map	*map;
	int		fd;

	if (argc != 2 || argv == NULL)
		return (print_arg_error(), NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (perror("Error\n"), NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\n"), free(map), NULL);
	if (count_config_line(map, fd) == false)
		return (free(map), close(fd), NULL);
	if (get_map_size(map, fd) == false)
		return (free(map), close(fd), NULL);
	close(fd);
	if (allocate_square_map(map) == false)
		return (free(map), NULL);
	return (map);
}
