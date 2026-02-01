/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:28:27 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/01 22:01:33 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

//args
//filename
//read
// texture file is exist?
// there are only 1, 0, E, S, W, N
// duplicate map
//outside
//inside
//

typedef struct s_color	t_color;
typedef struct s_config	t_config;
typedef struct s_map	t_map;

struct s_color
{
	int		red;
	int		green;
	int		blue;
}

struct s_config
{
	int		no_exist;
	int		ea_exist;
	int		so_exist;
	int		we_exist;
	int		f_exist;
	int		c_exist;
}

struct s_map
{
	int			cabfd;
	int			x;
	int			y;
	t_config	flags;
	t_color		floor_data;
	t_color		ceil_data;
	char		**mapdata;
}

bool	parse(int argc, char **argv, t_map *map)
{
	char	*fullpath;

	if (argv == NULL || game == NULL)
		return (false);
	if (argc != 2)
		return (false);
	fullpath = argv[1];
	if (is_valid_extention(fullpath, ".cab") == false)
		return (false);
	map->cabfd = open(cabfile, O_RONLY);
	if (map->cabfd < 0)
		return (perror("open"), false);
	if (parse_mapdata(map) == false)
		return (print_config_err(), false);
	return (true);
}

static bool parse_map_config(t_config *flags, char *config_str)
{
	if (flags == NULL || config_str == NULL)
		return (false);
	if (is_valid_color(config_str) == true)
	{
		if (ft_strncmp(config_str, "F ", 2) == true)
			flags->f_exist++;
		else if (ft_strncmp(config_str, "C ", 2) == true)
			flags->c_exist++;
		return (true);
	}
	if (is_valid_extention(config_str, ".xpm") == true)
	{
		if (ft_strncmp(config_str, "NO ", 3) == true)
			flags->no_exist++;
		else if (ft_strncmp(config_str, "EA ", 3) == true)
			flags->ea_exist++;
		else if (ft_strncmp(config_str, "SO ", 3) == true)
			flags->so_exist++;
		else if (ft_strncmp(config_str, "WE ", 3) == true)
			flags->we_exist++;
		return (true);
	}
	return (false);
}

static bool	is_configured_twice(t_config *flags)
{
	if (flags == NULL)
		return (false);
	if (flags->no_exist >= 2)
		return (false);
	else if (flags->ea_exist >= 2)
		return (false);
	else if (flags->so_exist >= 2)
		return (false);
	else if (flags->we_exist >= 2)
		return (false);
	else if (flags->f_exist >= 2)
		return (false);
	else if (flags->c_exist >= 2)
		return (false);
	return (true);
}

static bool is_config_line(char *line)
{
	char	keyword[6] = "NESWFC";
	int		i;

	if (line == NULL)
		return (false);
	i = 0;
	while (i < 6)
	{
		if (line[0] == keyword[i])
			return (true);
		i++;
	}
	return (false);
}

static bool	is_configured(t_config *flags)
{
	if (flags == NULL)
		return (false);
	if (flags->no_exist != 1)
		return (false);
	else if (flags->ea_exist != 1)
		return (false);
	else if (flags->so_exist != 1)
		return (false);
	else if (flags->we_exist != 1)
		return (false);
	else if (flags->f_exist != 1)
		return (false);
	else if (flags->c_exist != 1)
		return (false);
	return (true);
}

static bool	parse_mapdata(t_map *map)
{
	char	*line;
	int		row;

	if (map == NULL)
		return (false);
	while (is_configured(map) != true)
	{
		line = get_next_line(map->cabfd);
		if (line == NULL)
			return (false);
		if (is_config_line(line) == true)
		{
			if (parse_map_config(map->flags, line) == false || \
				is_configured_twice(map->flags) == true)
				return (free(line), false);
		}
		else if (line[0] != '\n')
			return (free(line), false);
		free(line);
	}
	while (1)
	{
		line = get_next_line(map->cabfd);
		if (line = NULL)
			break ;
		map->mapdata[row] = line;

