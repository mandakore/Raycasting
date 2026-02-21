/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 07:24:31 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/21 14:01:14 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_player(t_player *player, t_map *map)
{
	player->x = (float)(map->user_x * WALL);
	player->y = (float)(map->user_y * WALL);
	player->dire = map->dire;
	player->key_w = false;
	player->key_a = false;
	player->key_s = false;
	player->key_d = false;
	player->left_turn = false;
	player->right_turn = false;
}
