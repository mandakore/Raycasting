/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 07:24:29 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/29 12:00:01 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	update_direction(t_player *player)
{
	float	dire_speed;

	dire_speed = 0.02;
	if (player->left_turn)
		player->dire -= dire_speed;
	if (player->right_turn)
		player->dire += dire_speed;
	if (player->dire > 2 * PI)
		player->dire = 0;
	if (player->dire < 0)
		player->dire = 2 * PI;
}

static void	apply_movement(t_game *game, t_player *player,
							float add_x, float add_y)
{
	if (!touch(player->x + add_x, player->y, game))
		player->x += add_x;
	if (!touch(player->x, player->y + add_y, game))
		player->y += add_y;
}

void	move_player(t_game *game)
{
	t_player	*player;
	float		add_x;
	float		add_y;

	player = &game->player;
	update_direction(player);
	calc_move_delta(player, &add_x, &add_y);
	apply_movement(game, player, add_x, add_y);
}
