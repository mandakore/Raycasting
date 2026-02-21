/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/21 15:14:37 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	init_game_data(t_game *game, int argc, char **argv)
{
	t_map	*map;

	map = init_map(argc, argv);
	if (map == NULL)
		return (1);
	if (parse(map, argv[1]) != true)
		return (free_args(map), free(map), 1);
	init_player(&game->player, map);
	game->config = get_parsed_config(&map->config);
	game->map = get_parsed_map(map);
	if (game->config == NULL || game->map == NULL)
		return (free_args(map), free(map), 1);
	free_args(map);
	free(map);
	return (0);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (1);
	game->win = mlx_new_window(game->mlx, 1280, 720, "Ray");
	if (game->win == NULL)
		return (1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img == NULL)
		return (1);
	game->data = mlx_get_data_addr(game->img,
			&game->bit, &game->line_size, &game->type);
	set_wall_texture(game);
	return (0);
}

static void	set_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, E_WIN_CLOSE, 0, close_window, game);
	mlx_loop_hook(game->mlx, raycasting, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (init_game_data(&game, argc, argv) != 0)
		return (1);
	if (init_mlx(&game) != 0)
		return (1);
	set_hooks(&game);
	free_all(&game);
	return (0);
}
