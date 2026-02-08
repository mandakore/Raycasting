/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:43:01 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/07 14:43:46 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

unsigned int	apply_shading(unsigned int color, double distance)
{
	double	shade_factor;
	int		r;
	int		g;
	int		b;

	shade_factor = 1.0 - (distance / 15.0);
	if (shade_factor < 0.0)
		shade_factor = 0.0;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * shade_factor);
	g = (int)(g * shade_factor);
	b = (int)(b * shade_factor);
	return ((r << 16) | (g << 8) | b);
}
