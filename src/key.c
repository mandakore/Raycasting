/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:16:43 by atashiro          #+#    #+#             */
/*   Updated: 2025/11/06 17:59:01 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HIGHT / 2;
	player->dire = PI / 2;

	player->key_w = false;
	player->key_a = false;
	player->key_s = false;
	player->key_d = false;

	player->left_turn = false;
	player->right_turn = false;

}



int key_press(int keycode, t_player *player)
{
	if(keycode == W)
	{
		player->key_w = true;

	}
	if(keycode == S)
	{
		player->key_s = true;

	}
	if(keycode == A)
	{
		player->key_a = true;

	}
	if(keycode == D)
	{
		player->key_d = true;

	}
	if(keycode == LEFT)
	{
		player->left_turn = true;

	}
	if(keycode == RIGHT)
	{
		player->right_turn = true;

	}
	if (keycode == ESC)
		exit(1); //メモリリーク
	return 0;
}

int key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_w = false;
	if(keycode == S)
		player->key_s = false;
	if(keycode == A)
		player->key_a = false;
	if(keycode == D)
		player->key_d = false;
	if(keycode == LEFT)
		player->left_turn = false;
	if(keycode == RIGHT)
		player->right_turn = false;
	return 0;
}


void move_player(t_game *game)
{
	t_player *player;

	player = &game->player;

	int speed = 2;
	float dire_speed = 0.02;

	if (player->left_turn)
		player->dire -= dire_speed;
	if (player->right_turn)
		player->dire += dire_speed;
	if (player->dire > 2 * PI)
		player->dire = 0;
	if (player->dire < 0)
		player->dire = 2 * PI;

	float cos_angle = cos(player->dire);
	float sin_angle = sin(player->dire);

	float add_x = 0;
	float add_y = 0;

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
	{
		player->x += add_x;
	}
	if (!touch(player->x, player->y + add_y, game))
	{
		player->y += add_y;
	}

	// if (player->key_w)
	// {
	// 	player->x += cos_angle * speed;
	// 	player->y += sin_angle * speed;
	// }
	// if (player->key_s)
	// {
	// 	player->x -= cos_angle * speed;
	// 	player->y -= sin_angle * speed;
	// }
	// if (player->key_a)
	// {
	// 	player->x += sin_angle * speed;
	// 	player->y -= cos_angle * speed;
	// }
	// if (player->key_d)
	// {
	// 	player->x -= sin_angle * speed;
	// 	player->y += cos_angle * speed;
	// }


}





// int	key_handler(int keycode, t_game *game)
// {
// 	if (keycode == ESC)
// 	{
// 		close_window(game);
// 		return (0);
// 	}
// 	return 0;
// }
