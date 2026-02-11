/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:38:13 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/11 20:54:12 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	load_texture(t_game *game, int index, char *path)
{
	t_img	*tex;

	tex = &game->textures[index];
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error: Failed to load texture %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
}

void	set_wall_texture(t_game *game, t_config *config)
{
//	load_texture(game, 0, "textures/north.xpm");
//	load_texture(game, 1, "textures/south.xpm");
//	load_texture(game, 2, "textures/west.xpm");
//	load_texture(game, 3, "textures/east.xpm");
	load_texture(game, 0, config->no_path);
	load_texture(game, 1, config->ea_path);
	load_texture(game, 2, config->so_path);
	load_texture(game, 3, config->we_path);
}
