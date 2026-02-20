/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:58:59 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/20 12:07:46 by sohyamaz         ###   ########.fr       */
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

	if (map == NULL)
		return (NULL);
	parsed = (char **)ft_calloc(map->y + 1, sizeof(char *));
	if (parsed == NULL)
		return (NULL);
	i = 0;
	while (map->mapdata[i] != NULL)
	{
		parsed[i] = map->mapdata[i];
		i++;
	}
	return (parsed);
}

t_config	*get_parsed_config(t_config *config)
{
	t_config	*parsed;

	if (config == NULL)
		return (NULL);
	parsed = (t_config *)ft_calloc(1, sizeof(t_config));
	if (parsed == NULL)
		return (NULL);
	parsed->no_path = ft_strdup(config->no_path);
	parsed->ea_path = ft_strdup(config->ea_path);
	parsed->so_path = ft_strdup(config->so_path);
	parsed->we_path = ft_strdup(config->we_path);
	if (parsed->no_path == NULL || parsed->ea_path == NULL || \
parsed->so_path == NULL || parsed->we_path == NULL)
		return (free_pathes(parsed), free(parsed), NULL);
	parsed->f_color.red = config->f_color.red;
	parsed->f_color.green = config->f_color.green;
	parsed->f_color.blue = config->f_color.blue;
	parsed->c_color.red = config->c_color.red;
	parsed->c_color.green = config->c_color.green;
	parsed->c_color.blue = config->c_color.blue;
	return (parsed);
}
