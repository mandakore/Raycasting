/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:38:04 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/17 20:53:29 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	is_inside_of_range(t_board *board, int x, int y)
{
	if (board == NULL)
		return (false);
	if (x < 0 || x >= board->sheet_x)
		return (false);
	if (y < 0 || y >= board->sheet_y)
		return (false);
	return (true);
}

static bool	is_closed_inside(t_board *board, int org_x, int org_y)
{
	int		i;
	int		next_x;
	int		next_y;
	char	current;

	if (board == NULL || board->sheet == NULL)
		return (false);
	if (is_inside_of_range(board, org_x, org_y) == false)
	{
		printf("[inside]out of range (%d,%d)\n", org_x, org_y);
		return (true);
	}
	current = board->sheet[org_y][org_x];
	if (current == ' ' || current == 'o')
		return (false);
	if (current == 'i' || current == '1')
		return (true);
	board->sheet[org_y][org_x] = 'i';
	i = 0;
	while (i < 4)
	{
		next_x = org_x + board->dest_x[i];
		next_y = org_y + board->dest_y[i];
		if (is_closed_inside(board, next_x, next_y) == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_closed_outside(t_board *board, int org_x, int org_y)
{
	int		i;
	int		next_x;
	int		next_y;
	char	current;

	if (board == NULL || board->sheet == NULL)
		return (false);
	if (is_inside_of_range(board, org_x, org_y) == false)
		return (true);
	current = board->sheet[org_y][org_x];
	if (current == '0' || is_user(current) == true)
		return (false);
	if (current == '1' || current == 'o' || current == '\0')
		return (true);
	board->sheet[org_y][org_x] = 'o';
	i = 0;
	while (i < 4)
	{
		next_x = org_x + board->dest_x[i];
		next_y = org_y + board->dest_y[i];
		if (is_closed_outside(board, next_x, next_y) == false)
			return (false);
		i++;
	}
	return (true);
}

static void	apply_dest(t_board *board)
{
	if (board == NULL)
		return ;
	board->dest_x[0] = -1;
	board->dest_y[0] = 0;
	board->dest_x[1] = 0;
	board->dest_y[1] = -1;
	board->dest_x[2] = 0;
	board->dest_y[2] = 1;
	board->dest_x[3] = 1;
	board->dest_y[3] = 0;
	return ;
}

bool	is_map_closed(t_map *map)
{
	t_board	*board;

	if (map == NULL)
		return (false);
	board = ft_calloc(1, sizeof(t_board));
	if (board == NULL)
		return (false);
	board->sheet = get_big_sheet(map);
	if (board->sheet == NULL)
		return (free(board), false);
	board->sheet_x = (int)map->x + 2;
	board->sheet_y = (int)map->y + 2;
	apply_dest(board);
	printf("user at map (%d,%d) sheet (%d,%d)\n", map->user_x, map->user_y, map->user_x + 1, map->user_y + 1);
	printf("char at sheet user = '%c'\n", board->sheet[map->user_y + 1][map->user_x + 1]);
	if (is_closed_outside(board, 0, 0) != true)
		return (free_sheet(board->sheet), free(board), false);
	if (is_closed_inside(board, map->user_x + 1, map->user_y + 1) != true)
		return (free_sheet(board->sheet), free(board), false);
	free_sheet(board->sheet);
	free(board);
	printf("This is a valid map\n");
	return (true);
}
