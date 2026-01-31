/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:28:27 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/01/31 20:51:35 by sohyamaz         ###   ########.fr       */
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

typedef struct s_map	t_map;

struct s_map
{
	int		cabfd;
	int		map_lenx;
	int		map_leny;
	char	**mapdata;
}

bool	parse(int argc, char **argv, t_game *game)
{
	if (argv == NULL || game == NULL)
		return (false);
	if (argc != 2)
		return (false);
	//func_filecheck
	if (fd <= 1)
		return (false);
	if (is_wall_closed(t_map) == false)
	{
		free_map(map);
		return (false);
	}
	if (is_floar_exist(t_map) == false)
	{
		free_map(map);
		return (false);
	}
	return (true);
}

int    open_if_file_is_valid(char *argv1)
{
    int        fd;
    size_t    name_len;
    char    *filename;

    filename = ft_strrchr(argv1, '/');
    if (filename)
        filename++;
    else
        filename = argv1;
    name_len = ft_strlen(filename);
    if (name_len <= 4
        || ft_strncmp(filename + name_len - 4, ".ber", 4) != 0
        || name_len == 4)
        error_exit("invalid extension");
    fd = open(argv1, O_RDONLY);
    if (fd == -1)
        error_exit("failed to open file.");
    return (fd);
}

static bool	is_valid_cabfile(char *cabfile)
{
	char	*filename;
	size_t	fname_len;

	if (cabfile == NULL)
		return (false);
	filename = ft_strrchr(cabfile, '/');
	if (filename != NULL)
		filename++;
	else
		filename = cabfile;
	fname_len = ft_strlen(filename);
	if (fname_len <= 4)
		return (false);
	extention = filename + fname_len - 4;
	if (ft_strncmp(extention, ".cab", 4) != 0)
		return (false);
}

static bool	parse_cabfile(t_map *map, char *cabfile)
{
	if (cabfile == NULL)
		return (false);
	if (is_valid_cabfile(cabfile) == false)
		return (false);
	if (is_texture_file_exist)
}
