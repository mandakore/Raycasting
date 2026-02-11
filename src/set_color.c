/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 20:58:59 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/11 22:31:07 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	set_rgb_code(t_game *game, t_config *config)
{
	if (game == NULL || config == NULL)
		return ;
	game->ceil->red = config->c_color->red;
	game->ceil->green = config->c_color->green;
	game->ceil->blue = config->c_color->blue;
	game->floor->red = config->f_color->red;
	game->floor->green = config->f_color->green;
	game->floor->blue = config->f_color->blue;
	return ;
}
