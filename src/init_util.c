/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:41:27 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/10 01:28:12 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cab3d.h"

bool	get_map_size(t_map *map, char *fullpath)
{
	int		width;
	char	*line;

	if (map == NULL || fullpath == NULL)
		return (false);
	map->cubfd = open(fullpath, O_RONLY);
	if (map->cabfd < 0)
		return (perror("open"), false);
	width = 0;
	while (1)
	{
		line = get_next_line(map->cubfd);
		if (line == NULL)
			break ;
		width = ft_strlen(line) + 1;
		if (width > map->x)
			map->x = width;
		map->y++;
		free(line);
	}
	map->y = height + 1;
	close(cubfd);
	return (true);
}
