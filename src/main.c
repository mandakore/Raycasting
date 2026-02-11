/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/11 21:57:09 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

unsigned int	get_pixel_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = px / WALL;
	y = py / WALL;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->line_size + x * game->bit / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	*map

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (map == NULL)
		return (1);
	if (parse(argc, argv, map) != true)
		return (free_args(map), 1);
	init_player*(&game.player, map);
	set_wall_texture(&game);
	set_rgb_code(&game, map->config);
	game.map = get_parsed_map(map);
	if (game.map == NULL)
		return (free_args(map), 1);
	free_args(map);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1280, 720, "Ray");
	game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.data = mlx_get_data_addr(game.img, &game.bit,
			&game.line_size, &game.type);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, E_WIN_CLOSE, 0, close_window, &game);
	printf("Starting mlx_loop...\n");
	mlx_loop_hook(game.mlx, raycasting, &game);
	mlx_loop(game.mlx);
	free_all(&game);
}
