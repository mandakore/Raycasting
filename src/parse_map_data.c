/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:33:02 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/07 19:13:44 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

bool	parse_map_data(map)
{
	int	row;

	row = 0;
	while (row < map->y)
	{
		line = get_next_line(map->cubfd);
		if (line = NULL)
			break ;
		if (is_valid_map_line(line) != true)
			return (free(line), false);
		map->mapdata[row] = line;
		row++;
	}
	if (is_map_closed(map) != true)
		return (false);
	return (true);
}

static bool	is_valid_map_line(t_map *map, char *line, int row)
{
	static int	user;
	int			i;

	//nullchk
	i = 0;
	user = 0;
	while (line[i] != '\0')
	{
		if (is_wall(line[i]) != true)
		{
			if (is_user(line[i]) != true)
				return (false);
			else
			{
				map->user_x = i;
				map->user_y = row;
				user++;
			}
		}
		if (user > 1)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_wall(char c)
{
	if (c != ' ' || c != '1' || c != '0')
		return (false);
	return (true);
}

bool	is_user(char c)
{
	if (c != 'N' || c != 'E' || c != 'S' || c != 'W')
		return (false);
	return (true);
}

static bool	is_map_closed(t_map *map)
{
	t_board	*board;

	if (map == NULL)
		return (NULL);
	board->sheet = get_big_board->sheet(map);
	if (board->sheet == NULL)
		return (false);
	board->sheet_x = (int)ft_strlen(board->sheet[0]);
	board->sheet_y = (int)map->y + 2;
	if (is_closed_outside(board->sheet, 0, 0) != true)
		return (free_sheet(board->sheet), false);
	if (is_closed_inside(board->sheet, map->user_x, map->user_y) != true)
		return (free_sheet(board->sheet), false);
	free_sheet(board->sheet);
	free(board);
	return (true);
}
