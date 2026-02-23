/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:14:14 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/23 14:12:27 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	calc_move_delta(t_player *p, float *add_x, float *add_y)
{
	float	c;
	float	s;
	float	forward;
	float	side;

	c = cos(p->dire);
	s = sin(p->dire);
	forward = (p->key_w - p->key_s) * SPEED;
	side = (p->key_a - p->key_d) * SPEED;
	*add_x = (forward * c) + (side * s);
	*add_y = (forward * s) - (side * c);
}
