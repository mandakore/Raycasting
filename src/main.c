/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2025/10/30 21:12:28 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
# include "minilibx-linux/mlx.h"

int key_press(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = true;
	if(keycode == S)
		player->key_down = true;
	if(keycode == A)
		player->key_left = true;
	if(keycode == D)
		player->key_right = true;
	if(keycode == LEFT)
		player->left_turn = true;
	if(keycode == RIGHT)
		player->right_turn = true;
	return 0;
}

int key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = false;
	if(keycode == S)
		player->key_down = false;
	if(keycode == A)
		player->key_left = false;
	if(keycode == D)
		player->key_right = false;
	if(keycode == LEFT)
		player->left_turn = false;
	if(keycode == RIGHT)
		player->right_turn = false;
	return 0;
}



int	main()
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Ray");

	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	/*int mlx_hook(void *win_ptr, int event, int mask, int (*funct_ptr)(), void *param);*/
	mlx_loop(game.mlx);
}


// cc main.c -Lminilibx-linux -lmlx -lXext -lX11