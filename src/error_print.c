/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 23:52:50 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/18 15:22:27 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_prefix(void)
{
	printf("Error\n");
	return ;
}

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

void	print_invalid_extention(void)
{
	print_prefix();
	printf("Extention is not valid\n");
	printf("Give me a file with .cub extention\n");
	return ;
}

void	print_nomap_error(void)
{
	print_prefix();
	printf("There is no map in .cub file\n");
	return ;
}
