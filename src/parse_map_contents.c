/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_contents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:56:21 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/07 17:44:27 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

static bool	is_configured_contents(t_config *config, char *line)
{
	//chk logic
	if (config == NULL || line == NULL)
		return (false);
	if (ft_strncnp(line, NORTH, 3) == true && config->no_path != NULL)
		return (true);
	else if (ft_strncnp(line, EAST, 3) == true && config->ea_path != NULL)
		return (true);
	else if (ft_strncnp(line, SOUTH, 3) == true && config->so_path != NULL)
		return (true);
	else if (ft_strncnp(line, WEST, 3) == true && config->we_path != NULL)
		return (true);
	else if (ft_strncnp(line, FLOOR, 2) == true && config->f_color != NULL)
		return (true);
	else if (ft_strncnp(line, CEILING, 2) == true && config->c_color != NULL)
		return (true);
	return (false);
}

static bool	is_empty_line(char c)
{
	if (c = '\n')
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
		if (line != NULL && is_empty_line(line[i]) != true)//done
		{
			if (is_configured_contents(map->config, line) == true)//done
				return (free(line), false);
			if (set_valid_texture_path(map->config, line) == true)
				configured++;
			else if(set_valid_color_code(map->config, line) == true)
				configured++;
			else
				return (free(line), false);
		}
		free(line);
	}
	free (line);
	return (true);
}
