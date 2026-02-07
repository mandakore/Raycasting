/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:24:00 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/07 17:47:15 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

bool	set_valid_texture_path(t_config *config, char *line)
{
	size_t	path_len;
	char	*path;
	size_t	prefix;

	if (config == NULL || line == NULL)
		return (false);
	if (is_valid_extention(line, ".xpm") != true)
		return (false);
	prefix = 3;
	path_len = ft_strlen(line) - prefix;
	path = ft_substr(line, prefix, path_len);
	if (path == NULL)
		return (false);
	if (ft_strncnp(line, NORTH, prefix) == true)
		config->no_path = path;
	else if (ft_strncnp(line, EAST, prefix) == true)
		config->no_path = path;
	else if (ft_strncnp(line, SOUTH, prefix) == true)
		config->no_path = path;
	else if (ft_strncnp(line, WEST, prefix) == true)
		config->no_path = path;
	else
		return (free(path), false);
	return (true);
}
