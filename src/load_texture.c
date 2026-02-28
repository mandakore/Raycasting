/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:38:13 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/21 14:10:53 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	load_texture(t_game *game, int index, char *path)
{
	t_img	*tex;

	tex = &game->textures[index];
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: Failed to load texture %s\n", path);
		return (false);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
	return (true);
}

bool	set_wall_texture(t_game *game)
{
	if (game == NULL)
		return (false);
	if (load_texture(game, 0, game->config->no_path) == false)
		return (false);
	if (load_texture(game, 1, game->config->so_path) == false)
		return (false);
	if (load_texture(game, 2, game->config->we_path) == false)
		return (false);
	if (load_texture(game, 3, game->config->ea_path) == false)
		return (false);
	return (true);
}
