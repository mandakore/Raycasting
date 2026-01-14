/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:38:32 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/14 20:13:04 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		// int map_y = (int)(ray_y / WALL);
		float prev_x = ray_x - cos_angle * 0.1;
		// float prev_y = ray_y - sin_angle * 0.1;
		
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
