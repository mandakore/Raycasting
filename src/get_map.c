/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:58:59 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/11 22:33:26 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

//char	**get_map(void)
//{
//	char	**map;
//
//	map = malloc(sizeof(char *) * 12);
//	map[0] = "111111111111111";
//	map[1] = "100000000000001";
//	map[2] = "10000000000000111111";
//	map[3] = "11100010000000000001";
//	map[4] = "  10010000000000000111";
//	map[5] = "  10000001110000000001";
//	map[6] = "  10000000100000011111";
//	map[7] = "111000000000000001";
//	map[8] = "100000000000000001";
//	map[9] = "100000000000000001";
//	map[10] = "111111111111111111";
//	map[11] = NULL;
//	return (map);
//}
//
// char	**get_map(void)
// {
// 	char	**map;

// 	map = malloc(sizeof(char *) * 12);
// 	map[0] = "111";
// 	map[1] = "101";
// 	map[2] = "111";

// 	return (map);
// }

char	**get_parsed_map(t_map *map)
{
	char	**parsed;
	int		i;

	parsed = (char **)ft_calloc(map->y, sizeof(char *));
	if (parsed == NULL)
		return (NULL);
	i = 0;
	while (map->mapdata[i] != NULL)
	{
		parsed[i] = map->mapdata[i];
		i++;
	}
	parsed[i] = NULL;
	return (parsed);
}
