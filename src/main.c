/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/25 18:00:25 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	load_texture(t_game *game, int index, char *path)
{
	t_img	*tex;

	tex = &game->textures[index];
	tex->img = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: Failed to load texture %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
}

unsigned int	get_pixel_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}


bool touch(float px, float py, t_game *game)
{
	int x = px / WALL;
	int y = py / WALL;
	if(game->map[y][x] == '1')
		return true;
	return false;
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


int	main()
{
	t_game	game;

	init_player(&game.player);
	game.map = get_map();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Ray");
	game.img = mlx_new_image(game.mlx, WIDTH, HIGHT);
	game.data = mlx_get_data_addr(game.img, &game.bit, &game.line_size, &game.type);

	// テクスチャ読み込み
	load_texture(&game, 0, "textures/north.xpm");
	load_texture(&game, 1, "textures/south.xpm");
	load_texture(&game, 2, "textures/west.xpm");
	load_texture(&game, 3, "textures/east.xpm");

	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);


	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	// mlx_hook(game.win, 2, 1L<<0, key_handler, &game);-----eventがかぶってる
	/*int mlx_hook(void *win_ptr, int event, int mask, int (*funct_ptr)(), void *param);*/
	printf("Starting mlx_loop...\n");
	mlx_loop_hook(game.mlx, raycasting, &game);
	mlx_loop(game.mlx);
}


// cc main.c -Lminilibx-linux -lmlx -lXext -lX11
