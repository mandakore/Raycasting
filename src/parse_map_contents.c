/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_contents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:39:28 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/11 22:30:13 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	is_already_configured(t_config *config, char *line)
{
	if (config == NULL || line == NULL)
		return (true);
	if (ft_strncmp(line, NORTH, 3) == 0 && config->no_path != NULL)
		return (true);
	if (ft_strncmp(line, EAST, 3) == 0 && config->ea_path != NULL)
		return (true);
	if (ft_strncmp(line, SOUTH, 3) == 0 && config->so_path != NULL)
		return (true);
	if (ft_strncmp(line, WEST, 3) == 0 && config->we_path != NULL)
		return (true);
	if (ft_strncmp(line, FLOOR, 2) == 0 && config->f_color != NULL)
		return (true);
	if (ft_strncmp(line, CEILING, 2) == 0 && config->c_color != NULL)
		return (true);
	return (false);
}

static bool	is_empty_line(char c)
{
	if (c == '\n')
		return (true);
	return (false);
}

bool	parse_map_contents(t_map *map)
{
	char	*line;
	int		configured;

	if (map == NULL)
		return (false);
	configured = 0;
	while (configured < 6)
	{
		line = get_next_line(map->cubfd);
		if (line != NULL && is_empty_line(line[i]) != true)
		{
			if (is_already_configured(map->config, line) == true)
				return (free(line), false);
			if (set_valid_texture_path(map->config, line) == true)
				configured++;
			else if (set_valid_color_code(map->config, line) == true)
				configured++;
			else
				return (free(line), false);
		}
		free(line);
	}
	free (line);
	return (true);
}
