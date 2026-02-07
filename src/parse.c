/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:28:27 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/07 18:16:14 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

# ifndef NORTH
#  define NORTH "NO "
# endif

# ifndef EAST
#  define EAST "EA "
# endif

# ifndef SOUTH
#  define SOUTH "SO "
# endif

# ifndef WEST
#  define WEST "WE "
# endif

# ifndef FLOOR
#  define FLOOR "F "
# endif

# ifndef CEILING
#  define CEILING "C "
# endif

typedef struct s_color	t_color;
typedef struct s_config	t_config;
typedef struct s_map	t_map;
typedef struct s_board	t_board;

struct s_color
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
} ;

struct s_config
{
	char	*no_path;
	char	*ea_path;
	char	*so_path;
	char	*we_path;
	t_color	*f_color;
	t_color	*c_color;
} ;

struct s_board
{
	char	**sheet;
	int		sheet_x;
	int		sheet_y;
} ;

struct s_map
{
	int			cubfd;
	size_t		x;
	size_t		y;
	int			user_x;
	int			user_y;
	t_config	config;
	char		**mapdata;
} ;

bool	parse(int argc, char **argv, t_map *map)
{
	char	*fullpath;

	//args_err
	if (argv == NULL || map == NULL)
		return (false);
	if (argc != 2)
		return (false);
	//file_extention_err
	fullpath = argv[1];
	if (is_valid_extention(fullpath, ".cub") == false)
		return (false);
	//no_prvilege_err
	map->cubfd = open(cabfile, O_RONLY);
	if (map->cubfd < 0)
		return (perror("open"), false);
	//map_contents_err
	if (parse_map_contents(map) == false)
		return (print_config_err(), false);
	//mapdata_err
	if (parse_map_data(map) == false)
		return (print_map_err(), false);
	close(map->cubfd);
	return (true);
}
