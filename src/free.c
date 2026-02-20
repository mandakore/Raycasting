/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 01:05:35 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/21 03:49:01 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	free_map(char **map)
{
	if (!map)
		return ;
	free(map);
}

void	free_pathes(t_config *config)
{
	if (config == NULL)
		return ;
	if (config->no_path != NULL)
		free(config->no_path);
	if (config->ea_path != NULL)
		free(config->ea_path);
	if (config->so_path != NULL)
		free(config->so_path);
	if (config->we_path != NULL)
		free(config->we_path);
	return ;
}

void	free_mapdata(char **map)
{
	int	i;

	i = 0;
	if (map == NULL)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_args(t_map *map)
{
	free_pathes(&map->config);
	free_mapdata(map->mapdata);
	return ;
}

void	free_all(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_mapdata(game->map);
	free_pathes(game->config);
	free(game->config);
	return ;
}
