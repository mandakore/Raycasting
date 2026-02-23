/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_informations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:39:28 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/23 13:47:20 by sohyamaz         ###   ########.fr       */
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
	if (ft_strncmp(line, FLOOR, 2) == 0 && config->f_color.is_configured != 0)
		return (true);
	if (ft_strncmp(line, CEILING, 2) == 0 && config->c_color.is_configured != 0)
		return (true);
	return (false);
}

static bool	is_empty_line(char c)
{
	if (c == '\n')
		return (true);
	return (false);
}

static bool	set_config(t_config *config, char *line)
{
	char	c;

	if (config == NULL || line == NULL)
		return (false);
	c = line[0];
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		if (set_valid_texture_path(config, line) == false)
			return (print_invalid_wall(), false);
		return (true);
	}
	else if (c == 'F' || c == 'C')
	{
		if (set_valid_color_code(config, line) == false)
			return (print_invalid_color(), false);
		return (true);
	}
	else
		return (print_unexpected_char(), false);
}

bool	parse_config_informations(t_map *map)
{
	char	*line;
	size_t	i;

	if (map == NULL)
		return (false);
	i = 0;
	while (i < map->config_line)
	{
		line = get_next_line(map->cubfd);
		if (line == NULL)
			break ;
		if (is_empty_line(line[0]) != true)
		{
			if (is_already_configured(&map->config, line) == true)
				return (print_dup_config_err(), free(line), false);
			if (set_config(&map->config, line) == false)
				return (free(line), false);
		}
		free(line);
		i++;
	}
	return (true);
}
