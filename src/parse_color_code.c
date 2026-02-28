/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:39:16 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/27 22:49:07 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	is_valid_code(t_rgb color)
{
	if (color.red > 255)
		return (false);
	else if (color.green > 255)
		return (false);
	else if (color.blue > 255)
		return (false);
	return (true);
}

static void	get_color_code(t_rgb *color, char *code)
{
	int	i;

	if (color == NULL || code == NULL)
		return ;
	i = 0;
	while (code[i] != ',')
	{
		color->red = (color->red * 10) + (code[i] - '0');
		i++;
	}
	i++;
	while (code[i] != ',')
	{
		color->green = (color->green * 10) + (code[i] - '0');
		i++;
	}
	i++;
	while (code[i] != '\0' && code[i] != '\n')
	{
		color->blue = (color->blue * 10) + (code[i] - '0');
		i++;
	}
	return ;
}

static bool	is_valid_color_input(char *input)
{
	int	i;
	int	itr;

	if (input == NULL)
		return (false);
	i = 0;
	itr = 0;
	while (input[i] != '\n' && input[i] != '\0')
	{
		if (input[i] == ',')
		{
			if (itr < 2)
				itr++;
			else
				return (false);
		}
		else if (input[i] < '0' || input[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	set_valid_color_code(t_config *config, char *line)
{
	char	*code;

	if (config == NULL || line == NULL)
		return (false);
	code = line + 2;
	if (is_valid_color_input(code) == false)
		return (false);
	if (ft_strncmp(line, FLOOR, 2) == 0)
	{
		get_color_code(&config->f_color, code);
		if (is_valid_code(config->f_color) != true)
			return (false);
		config->f_color.is_configured = 1;
	}
	else if (ft_strncmp(line, CEILING, 2) == 0)
	{
		get_color_code(&config->c_color, code);
		if (is_valid_code(config->c_color) != true)
			return (false);
		config->c_color.is_configured = 1;
	}
	else
		return (false);
	return (true);
}
