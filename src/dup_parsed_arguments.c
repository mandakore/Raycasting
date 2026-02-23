/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_parsed_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:58:59 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/23 14:13:16 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		parsed[i] = ft_strdup(map->mapdata[i]);
		if (parsed[i] == NULL)
			return (perror("Error\n"), free_mapdata(parsed), NULL);
		printf("%d: %s\n", i, parsed[i]);
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
