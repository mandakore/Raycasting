/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:39:51 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/17 20:33:23 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	put_single_line(char *sheet, char *line, size_t limit)
{
	size_t	i;

	if (sheet == NULL || line == NULL)
		return ;
	i = 0;
	while (i < limit && line[i] != '\0')
	{
		sheet[i + 1] = line[i];
		i++;
	}
	return ;
}

void	free_sheet(char **sheet)
{
	size_t	i;

	if (sheet == NULL)
		return ;
	i = 0;
	while (1)
	{
		if (sheet[i] == NULL)
			break ;
		free(sheet[i]);
		i++;
	}
//	while (sheet[i] != NULL)
//	{
//		free(sheet[i]);
//		i++;
//	}
	free(sheet);
	return ;
}

bool	is_user(char c)
{
	if (c != 'N' && c != 'E' && c != 'S' && c != 'W')
		return (false);
	return (true);
}

char	**get_big_sheet(t_map *map)
{
	char	**sheet;
	size_t	y;

	sheet = (char **)ft_calloc((map->y + 3), sizeof(char *));
	if (sheet == NULL)
		return (NULL);
	y = 0;
	while (y < map->y + 2)
	{
		sheet[y] = (char *)ft_calloc((map->x + 2), sizeof(char));
		if (sheet[y] == NULL)
			return (free_sheet(sheet), NULL);
		sheet[y] = (char *)ft_memset(sheet[y], ' ', map->x + 1);
		if (y > 0 && y < map->y + 1)
			put_single_line(sheet[y], map->mapdata[y - 1], map->x);
		y++;
	}
	return (sheet);
}
