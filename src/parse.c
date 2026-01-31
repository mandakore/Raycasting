/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:28:27 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/01/31 20:12:06 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

//args
//filename
//read
// texture file is exist?
// there are only 1, 0, E, S, W, N
// duplicate map
//outside
//inside
//

bool	parse(int argc, char **argv, t_game *game)
{
	if (argv == NULL || game == NULL)
		return (false);
	if (argc != 2)
		return (false);
	//func_filecheck
	if (fd <= 1)
		return (false);
	if (parse_cab_file(fd, t_map) == false)
		return (false);
	if (is_wall_closed(t_map) == false)
	{
		free_map(map);
		return (false);
	}
	if (is_floar_exist(t_map) == false)
	{
		free_map(map);
		return (false);
	}
	return (true);
}
