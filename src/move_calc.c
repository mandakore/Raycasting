/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:14:14 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/28 09:17:03 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


static void	move_w(t_player *p, float c, float s, float *x, float *y)
{
	int	speed;

	speed = 1;
	if (p->key_w)
	{
		*x += c * speed;
		*y += s * speed;
	}
}

static void	move_s(t_player *p, float c, float s, float *x, float *y)
{
	int	speed;

	speed = 1;
	if (p->key_s)
	{
		*x -= c * speed;
		*y -= s * speed;
	}
}


static void	move_a(t_player *p, float c, float s, float *x, float *y)
{
	int	speed;

	speed = 1;
	if (p->key_a)
	{
		*x += s * speed;
		*y -= c * speed;
	}
}

static void	move_d(t_player *p, float c, float s, float *x, float *y)
{
	int	speed;

	speed = 1;
	if (p->key_d)
	{
		*x -= s * speed;
		*y += c * speed;
	}
}

void	calc_move_delta(t_player *player, float *add_x, float *add_y)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->dire);
	sin_angle = sin(player->dire);
	*add_x = 0;
	*add_y = 0;
	move_w(player, cos_angle, sin_angle, add_x, add_y);
	move_s(player, cos_angle, sin_angle, add_x, add_y);
	move_a(player, cos_angle, sin_angle, add_x, add_y);
	move_d(player, cos_angle, sin_angle, add_x, add_y);
}
