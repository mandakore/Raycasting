/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 07:24:31 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/01 19:37:54 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 8;
	player->y = HEIGHT / 16;
	player->dire = PI;
	player->key_w = false;
	player->key_a = false;
	player->key_s = false;
	player->key_d = false;
	player->left_turn = false;
	player->right_turn = false;
}
