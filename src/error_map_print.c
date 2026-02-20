/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_map_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:23:25 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/18 20:00:20 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_invalid_symbol(void)
{
	print_prefix();
	printf("There is at least one error symbol in your map\n");
	return ;
}

void	print_player_error(int player)
{
	print_prefix();
	if (player == 0)
		printf("There is no player in your map\n");
	else
		printf("There are two or more player in your map\n");
	return ;
}

void	print_torned_floor(void)
{
	print_prefix();
	printf("There is at least one hole on the floor in your map\n");
	return ;
}

void	print_wall_error(char c)
{
	print_prefix();
	if (is_user(c) == true)
		printf("User will sporn at out of range\n");
	else
		printf("This map is not surrounded by wall\n");
	return ;
}
