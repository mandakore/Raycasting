/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:22:08 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/07 17:48:40 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

static bool	is_valid_code(t_color *color)
{
	if (color == NULL)
		return (false);
	if (color->red > 255)
		return (false);
	else if (color->green > 255)
		return (false);
	else if (color->blue > 255)
		return (false);
	return (true);
}

static void	get_color_code(t_color *color, char *code)
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
	size_t	prefix;

	if (config == NULL || line == NULL)
		return (false);
	prefix = 2;
	code_len = ft_strlen(line) - prefix;
	code = ft_substr(line, prefix, code_len);
	if (code == NULL)
		return (false);
	if (ft_strncnp(line, FLOOR, prefix) == true)
	{
		get_color_code(config->f_color, line + 2);
		if (is_valid_code(config->f_color) != true)
			return (false);
	}
	else if (ft_strncnp(line, CEILING, prefix) == true)
	{
		get_color_code(config->c_color, line + 2);
		if (is_valid_code(config->c_color) != true)
			return (false);
	}
	return (true);
}
