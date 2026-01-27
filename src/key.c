/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:16:43 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/28 05:21:49 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 8;
	player->y = HIGHT / 16;
	player->dire = PI;
	player->key_w = false;
	player->key_a = false;
	player->key_s = false;
	player->key_d = false;
	player->left_turn = false;
	player->right_turn = false;
}

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

void	move_player(t_game *game)
{
	t_player	*player;
	int			speed;
	float		dire_speed;
	float		cos_angle;
	float		sin_angle;
	float		add_x;
	float		add_y;

	player = &game->player;
	speed = 1;
	dire_speed = 0.03;
	cos_angle = cos(player->dire);
	sin_angle = sin(player->dire);
	if (player->left_turn)
		player->dire -= dire_speed;
	if (player->right_turn)
		player->dire += dire_speed;
	if (player->dire > 2 * PI)
		player->dire = 0;
	if (player->dire < 0)
		player->dire = 2 * PI;
	add_x = 0;
	add_y = 0;
	if (player->key_w)
	{
		add_x += cos_angle * speed;
		add_y += sin_angle * speed;
	}
	if (player->key_s)
	{
		add_x -= cos_angle * speed;
		add_y -= sin_angle * speed;
	}
	if (player->key_a)
	{
		add_x += sin_angle * speed;
		add_y -= cos_angle * speed;
	}
	if (player->key_d)
	{
		add_x -= sin_angle * speed;
		add_y += cos_angle * speed;
	}
	if (!touch(player->x + add_x, player->y, game))
		player->x += add_x;
	if (!touch(player->x, player->y + add_y, game))
		player->y += add_y;
}
