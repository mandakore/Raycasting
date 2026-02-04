/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:26:21 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/04 18:43:00 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	get_line_len(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
		i++;
	return (i);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}
