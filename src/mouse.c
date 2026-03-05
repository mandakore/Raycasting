/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 02:30:00 by atashiro          #+#    #+#             */
/*   Updated: 2026/03/03 17:23:55 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	mouse_move(int x, int y, t_game *game)
{
	int	center_x;

	(void)y;
	if (!game->player.mouse_captured)
		return (0);
	center_x = WIDTH / 2;
	game->player.mouse_dx = (float)(x - center_x);
	mlx_mouse_move(game->mlx, game->win, center_x, HEIGHT / 2);
	return (0);
}
