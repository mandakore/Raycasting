/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:16:43 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/28 07:26:59 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == W)
		game->player.key_w = true;
	if (keycode == S)
		game->player.key_s = true;
	if (keycode == A)
		game->player.key_a = true;
	if (keycode == D)
		game->player.key_d = true;
	if (keycode == LEFT)
		game->player.left_turn = true;
	if (keycode == RIGHT)
		game->player.right_turn = true;
	if (keycode == ESC)
	{
		free_all(game);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_w = false;
	if (keycode == S)
		player->key_s = false;
	if (keycode == A)
		player->key_a = false;
	if (keycode == D)
		player->key_d = false;
	if (keycode == LEFT)
		player->left_turn = false;
	if (keycode == RIGHT)
		player->right_turn = false;
	return (0);
}
