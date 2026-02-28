/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:49:39 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/27 23:07:14 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	init_game_data(t_game *game, int argc, char **argv)
{
	t_map	*map;

  map = init_map(argc, argv);
  if (map == NULL)
    return (false);
  if (parse(map, argv[1]) != true)
    return (free_args(map), free(map), false);
  init_player(&game->player, map);
  game->config = get_parsed_config(&map->config);
  game->map = get_parsed_map(map);
  if (game->config == NULL || game->map == NULL)
    return (free_args(map), free(map), false);
  free_args(map);
  free(map);
  return (true);
}

static bool	init_mlx(t_game *game)
{
  game->mlx = mlx_init();
  if (game->mlx == NULL)
    return (false);
  game->win = mlx_new_window(game->mlx, 1280, 720, "cub3D");
  if (game->win == NULL)
    return (false);
  game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
  if (game->img == NULL)
    return (false);
	game->data = mlx_get_data_addr(game->img,
			&game->bit, &game->line_size, &game->type);
  if (set_wall_texture(game) == false)
    return (false);
  return (true);
}

static void	set_hooks(t_game *game)
{
  mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
  mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
  mlx_hook(game->win, MotionNotify, PointerMotionMask, mouse_move, game);
  mlx_hook(game->win, ClientMessage, NoEventMask, mlx_loop_end, game->mlx);
  mlx_loop_hook(game->mlx, raycasting, game);
  mlx_mouse_hide(game->mlx, game->win);
  mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
}

int	main(int argc, char **argv)
{
	t_game	game;

  if (init_game_data(&game, argc, argv) == false)
    return (free_duplicated_data(&game), 1);
  if (init_mlx(&game) == false)
    return (free_all(&game), 1);
  set_hooks(&game);
  mlx_loop(game.mlx);
  free_all(&game);
  return (0);
}
