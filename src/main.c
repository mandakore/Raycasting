/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/10 13:54:21 by sohyamaz         ###   ########.fr       */
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

	move_player(game);
	clear_player(game);


	float fraction = PI / 2 / WIDTH;
	float current_angle = player->dire - PI / 4;
	int i = 0;

	while(i < WIDTH)
	{
		float ray_x = player->x;
		float ray_y = player->y;
		float cos_angle = cos(current_angle);
		float sin_angle = sin(current_angle);

		int side = 0; // 0: NS, 1: EW (簡易判定)

		// DDAではないため、簡易的なステップで衝突判定
		// 精度向上のためステップを細かくする
		while(!touch(ray_x, ray_y, game))
		{
			ray_x += cos_angle * 0.1; // 精度向上のためステップを小さく
			ray_y += sin_angle * 0.1;
		}

		int map_x = (int)(ray_x / WALL);
//		int map_y = (int)(ray_y / WALL);
		float prev_x = ray_x - cos_angle * 0.1;
//		float prev_y = ray_y - sin_angle * 0.1;

		if ((int)(prev_x / WALL) != map_x)
			side = 1; // 垂直壁(東西)
		else
			side = 0; // 水平壁(南北)

		// 方角判定
		int tex_idx;
		if (side == 1)
		{
			if (cos_angle > 0) tex_idx = 3; // East
			else tex_idx = 2; // West
		}
		else
		{
			if (sin_angle > 0) tex_idx = 1; // South
			else tex_idx = 0; // North
		}

		current_angle += fraction;

		float dist = distance(ray_x - player->x, ray_y - player->y);
		// 魚眼補正
		// float angle_diff = current_angle - fraction - player->dire; // current_angleは既にインクリメントされているため戻す
		// dist = dist * cos(angle_diff);

		float height = (WALL / dist) * (WIDTH / 2); // 高さ計算の係数は調整が必要かも
		int start_y = (HIGHT - height) / 2;
		if (start_y < 0) start_y = 0;
		int end_y = start_y + height;
		if (end_y >= HIGHT) end_y = HIGHT - 1;

		// テクスチャX座標の計算
		float wall_x;
		if (side == 0) wall_x = ray_x;
		else           wall_x = ray_y;
		wall_x -= floor(wall_x / WALL) * WALL; // 壁内のオフセット(0~WALL)

		int tex_x = (int)(wall_x / WALL * game->textures[tex_idx].width);
		if ((side == 0 && sin_angle > 0) || (side == 1 && cos_angle < 0))
			tex_x = game->textures[tex_idx].width - tex_x - 1;

		int y = start_y;
		while(y < end_y)
		{
			int d = y * 256 - HIGHT * 128 + height * 128;
			int tex_y = ((d * game->textures[tex_idx].height) / height) / 256;

			// 安全策
			if (tex_y < 0) tex_y = 0;
			if (tex_y >= game->textures[tex_idx].height) tex_y = game->textures[tex_idx].height - 1;

			unsigned int color = get_pixel_color(&game->textures[tex_idx], tex_x, tex_y);
			put_pixel(i, y, color, game);
			y++;
		}
		i++;
	}
	draw_square(player->x, player->y, 10, 0xFFFFFF, game); // ミニマップは一旦コメントアウト?
	create_map(game); //
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

	// テクスチャ読み込み
	load_texture(&game, 0, "textures/north.xpm");
	load_texture(&game, 1, "textures/south.xpm");
	load_texture(&game, 2, "textures/west.xpm");
	load_texture(&game, 3, "textures/east.xpm");

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
