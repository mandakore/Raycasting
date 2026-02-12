/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:39:16 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/13 02:19:44 by sohyamaz         ###   ########.fr       */
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
	while (code[i] != '\0')
	{
		color->blue = (color->blue * 10) + (code[i] - '0');
		i++;
	}
	return ;
}

bool	set_valid_color_code(t_config *config, char *line)
{
	size_t	code_len;
	char	*code;

	if (config == NULL || line == NULL)
		return (false);
	code_len = ft_strlen(line) - 2;
	code = ft_substr(line, 2, code_len);
	if (code == NULL)
		return (false);
	if (ft_strncmp(line, FLOOR, 2) == 0)
	{
		get_color_code(&config->f_color, line + 2);
		if (is_valid_code(config->f_color) != true)
			return (false);
		config->f_color.is_configured = 1;
	}
	else if (ft_strncmp(line, CEILING, 2) == 0)
	{
		get_color_code(&config->c_color, line + 2);
		if (is_valid_code(config->c_color) != true)
			return (false);
		config->c_color.is_configured = 1;
	}
	else
		return (false);
	return (true);
}
