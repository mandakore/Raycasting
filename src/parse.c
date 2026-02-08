/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:38:48 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/09 05:39:00 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse(int argc, char **argv, t_map *map)
{
	char	*fullpath;

	if (argv == NULL || map == NULL)
		return (false);
	if (argc != 2)
		return (false);
	fullpath = argv[1];
	if (is_valid_extention(fullpath, ".cub") == false)
		return (false);
	map->cubfd = open(cabfile, O_RONLY);
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
