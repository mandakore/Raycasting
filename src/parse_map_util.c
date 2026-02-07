/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:34:34 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/07 19:13:50 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

char	**get_big_sheet(t_map *map)
{
	char	**sheet;
	size_t	y;

	sheet = (char **)ft_calloc((map->y + 2), sizeof(char *));
	if (sheet == NULL)
		return (false);
	y = 0;
	while (y < map->y + 2)
	{
		x = 0;
		sheet[y] = (char *)malloc((map->x + 2) * sizeof(char));
		if (sheet[y] == NULL)
			return (free_sheet(sheet), false);
		if (y == 0 || y == map->y + 1)
			sheet[y] = (char *)ft_memset(sheet[y], ' ', map->x + 2);
		else
		{
			while (x < map->x)
			{
				sheet[y][x + 1] = map->mapdata[y - 1][x];
				x++;
			}
		}
		y++;
	}
	return (sheet);
}

static void	free_sheet(char **sheet, size_t len)
{
	size_t	i;

	if (sheet == NULL)
		return ;
	i = 0;
	while (i < len)
	{
		free(sheet[i]);
		i++;
	}
	free(sheet);
	return ;
}

static bool	is_closed_outside(t_board *board, int org_x, int org_y)
{
	int	dest_x[] = {-1, 0, 0, 1};
	int	dest_y[] = {0, -1, 1, 0};
	int	i;

	if (board == NULL || board->sheet == NULL)
		return (false);
	if (org_x < 0 || org_x >= board->sheet_x)
		return (true);
	else if (org_y < 0 || org_y >= board->sheet_y)
		return (true);
	if (board->sheet[org_y][org_x] == '.' || board->sheet[org_y][org_x] == '1')
		return (true);
	else if (board->sheet[org_y][org_x] == '0' \
		|| is_user(board->sheet[org_y][org_x]) == true)
		return (false);
	board->sheet[org_y][org_x] = '.';
	i = 0;
	while (i < 4)
	{
		if (is_closed_outside(board, \
			org_x + dest_x[i], org_y + dest_y[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
