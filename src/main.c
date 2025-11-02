/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2025/11/02 19:13:18 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"



void put_pixel(int x, int y, int color, t_game *game)
{
	if(x >= WIDTH || y >= HIGHT || x < 0 || y < 0)
		return;

	int index = y * game->line_size + x * game->bit / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}



void draw_square(int x, int y, int size, int color, t_game *game)
{
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);//for修正
}



int raycasting(t_game *game)
{
	t_player	*player = &game->player;
	move_player(player);
	draw_square(player->x, player->y, 10, 0xFFFFFF, game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}



int	main()
{
	t_game	game;

	init_player(&game.player);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Ray");
	game.img = mlx_new_image(game.mlx, WIDTH, HIGHT);
	game.data = mlx_get_data_addr(game.img, &game.bit, &game.line_size, &game.type);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);

	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	// mlx_hook(game.win, 2, 1L<<0, key_handler, &game);-----eventがかぶってる
	/*int mlx_hook(void *win_ptr, int event, int mask, int (*funct_ptr)(), void *param);*/
	printf("Starting mlx_loop...\n");
	mlx_loop_hook(game.mlx, raycasting, &game);
	mlx_loop(game.mlx);
}


// cc main.c -Lminilibx-linux -lmlx -lXext -lX11