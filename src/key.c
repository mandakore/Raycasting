/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:16:43 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/27 17:00:30 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->player.key_w = true;
	if (keycode == XK_s)
		game->player.key_s = true;
	if (keycode == XK_a)
		game->player.key_a = true;
	if (keycode == XK_d)
		game->player.key_d = true;
	if (keycode == XK_Left)
		game->player.left_turn = true;
	if (keycode == XK_Right)
		game->player.right_turn = true;
	if (keycode == XK_Escape)
	{
		free_all(game);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->player.key_w = false;
	if (keycode == XK_s)
		game->player.key_s = false;
	if (keycode == XK_a)
		game->player.key_a = false;
	if (keycode == XK_d)
		game->player.key_d = false;
	if (keycode == XK_Left)
		game->player.left_turn = false;
	if (keycode == XK_Right)
		game->player.right_turn = false;
	return (0);
}
