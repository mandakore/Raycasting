/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_init_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:32:52 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/23 14:14:55 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_arg_error(void)
{
	print_prefix();
	printf("Given args are not valid\n");
	printf("Usage: ./game path_of_the_config_file.cub\n");
	return ;
}

void	print_lack_of_config(void)
{
	print_prefix();
	printf("There is not enough configure infomation\n");
	return ;
}

void	print_nomap_error(void)
{
	print_prefix();
	printf("There is no map in .cub file\n");
	return ;
}

void	print_too_big_map(void)
{
	print_prefix();
	printf("Given map is too big to run this project\n");
	return ;
}
