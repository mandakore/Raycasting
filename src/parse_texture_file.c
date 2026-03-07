/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:40:18 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/03/07 13:20:23 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static char	*get_path(char *line)
{
	size_t	path_len;
	char	*path;
	size_t	prefix;
	int		fd;

	if (line == NULL)
		return (NULL);
	prefix = 3;
	path_len = ft_strlen(line) - prefix;
	path = ft_substr(line, prefix, path_len);
	if (path == NULL)
		return (NULL);
	path[path_len - 1] = '\0';
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Error\ninvalid_texture_path"), free(path), NULL);
	close(fd);
	return (path);
}

bool	set_valid_texture_path(t_config *config, char *line)
{
	char	*path;
	size_t	prefix;

	if (config == NULL || line == NULL)
		return (false);
	if (is_valid_extention(line, ".xpm\n") != true)
		return (false);
	path = get_path(line);
	if (path == NULL)
		return (false);
	prefix = 3;
	if (ft_strncmp(line, NORTH, prefix) == 0)
		config->no_path = path;
	else if (ft_strncmp(line, EAST, prefix) == 0)
		config->ea_path = path;
	else if (ft_strncmp(line, SOUTH, prefix) == 0)
		config->so_path = path;
	else if (ft_strncmp(line, WEST, prefix) == 0)
		config->we_path = path;
	else
		return (free(path), false);
	return (true);
}
