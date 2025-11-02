/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 01:16:43 by atashiro          #+#    #+#             */
/*   Updated: 2025/11/02 20:02:39 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HIGHT / 2;

	player->key_w = false;
	player->key_a = false;
	player->key_s = false;
	player->key_d = false;
}



int key_press(int keycode, t_player *player)
{
	if(keycode == W)
	{
		player->key_w = true;
		printf("W key pressed\n");
	}
	if(keycode == S)
	{
		player->key_s = true;
		printf("S key pressed\n");
	}
	if(keycode == A)
	{
		player->key_a = true;
		printf("W key pressed\n");
	}
	if(keycode == D)
	{
		player->key_d = true;
		printf("D key pressed\n");
	}
	if(keycode == LEFT)
	{
		player->left_turn = true;
		printf("LEFT key pressed\n");
	}
	if(keycode == RIGHT)
	{
		player->right_turn = true;
		printf("RIGHT key pressed\n");
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


void move_player(t_player *player)
{
	int speed = 3;

	if (player->key_w)
	{
		player->y -= speed;
	}
	if (player->key_s)
	{
		player->y += speed;
	}
	if (player->key_a)
	{
		player->x -= speed;
	}
	if (player->key_d)
	{
		player->x += speed;
	}
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
