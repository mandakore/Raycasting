/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2025/11/02 20:09:36 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char **get_map(void)
{
	char **map = malloc(sizeof(char *) * 12);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "10000000000000111111";
	map[3] = "11100010000000000001";
	map[4] = "  10010000000000000111";
	map[5] = "  10000001110000000001";
	map[6] = "  10000000100000011111";
	map[7] = "111000000000000001";
	map[8] = "100000000000000001";
	map[9] = "100000000000000001";
	map[10] = "111111111111111111";
	map[11] = NULL;
	return (map);
}

void put_pixel(int x, int y, int color, t_game *game)
{
	if(x >= WIDTH || y >= HIGHT || x < 0 || y < 0)
		return;

	int index = y * game->line_size + x * game->bit / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;//コピペなので注意
}



void draw_square(int x, int y, int size, int color, t_game *game)
{
	int i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}


void clear_player(t_game *game)
{
	int y = 0;
	while (y < HIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}


void create_map(t_game *game)
{
	char **map = game->map;
	int color = 0xADFF2F;

	int x;
	int y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * WALL, y * WALL, WALL, color, game);
			x++;
		}
		y++;
	}
}



int raycasting(t_game *game)
{
	t_player	*player = &game->player;
	move_player(player);
	clear_player(game);
	draw_square(player->x, player->y, 10, 0xFFFFFF, game);
	create_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}



int	main()
{
	t_game	game;

	init_player(&game.player);
	game.map = get_map();
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