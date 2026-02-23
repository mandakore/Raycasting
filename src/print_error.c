/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 23:52:50 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/23 14:14:49 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	print_prefix(void)
{
	printf("Error\n");
	return ;
}

void	print_invalid_extention(void)
{
	print_prefix();
	printf("Extention is not valid\n");
	printf("Give me a file with .cub extention\n");
	return ;
}
