/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2025/10/31 01:32:29 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main()
{
	t_game	game;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Ray");

	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game);
	// mlx_hook(game.win, 2, 1L<<0, key_handler, &game);-----eventがかぶってる
	/*int mlx_hook(void *win_ptr, int event, int mask, int (*funct_ptr)(), void *param);*/
	printf("Starting mlx_loop...\n");
	mlx_loop(game.mlx);
}


// cc main.c -Lminilibx-linux -lmlx -lXext -lX11