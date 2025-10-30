/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2025/10/30 21:49:39 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
# include "minilibx-linux/mlx.h"

int key_press(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_w = true;
	if(keycode == S)
		player->key_s = true;
	if(keycode == A)
		player->key_a = true;
	if(keycode == D)
		player->key_d = true;
	if(keycode == LEFT)
		player->left_turn = true;
	if(keycode == RIGHT)
		player->right_turn = true;
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


int	key_handler(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		close_window(game);
		return (0);
	}
	return 0;

//要修正：この中に全部入れちゃう？
}



int	main()
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Ray");

	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	mlx_hook(game.win, 2, 1L<<0, key_handler, &game);
	/*int mlx_hook(void *win_ptr, int event, int mask, int (*funct_ptr)(), void *param);*/
	printf("Starting mlx_loop...\n");
	mlx_loop(game.mlx);
}


// cc main.c -Lminilibx-linux -lmlx -lXext -lX11