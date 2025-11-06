/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:25:28 by atashiro          #+#    #+#             */
/*   Updated: 2025/11/06 19:34:34 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}


float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}