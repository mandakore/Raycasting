/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_config_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 01:41:00 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/18 03:38:02 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_invalid_wall(void)
{
	print_prefix();
	printf("Wall setting is invalid\n");
	return ;
}

void	print_invalid_color(void)
{
	print_prefix();
	printf("Color of floor/Ceiling is invalid\n");
	return ;
}

void	print_dup_config_err(void)
{
	print_prefix();
	printf("This map has duplicated congfig contents\n");
	return ;
}
