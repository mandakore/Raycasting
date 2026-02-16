/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:38:48 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/17 04:39:44 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool	parse(t_map *map, char *path)
{
	if (map == NULL || path == NULL)
		return (false);
	if (is_valid_extention(path, ".cub") == false)
		return (false);
	map->cubfd = open(path, O_RDONLY);
	if (map->cubfd < 0)
		return (perror("open"), false);
	if (parse_map_contents(map) == false)
		return (false);
	if (parse_map_data(map) == false)
		return (false);
	close(map->cubfd);
	return (true);
}

//Need to make print error func
