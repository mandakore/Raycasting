/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:50:27 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/25 19:00:25 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

# define E_KEY_PRESS 2
# define E_WIN_RESIZE 9
# define E_WIN_CLOSE 17

# define HIGHT 720
# define WIDTH 1280

# define WALL 16

# define PI 3.14159265358979323



# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "mlx/mlx.h"

typedef struct s_player
{

	float		x;
	float		y;
	float		dire;

	bool	key_w;
	bool	key_s;
	bool	key_a;
	bool	key_d;

	bool left_turn;
	bool right_turn;

}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	char		*data;
	void		*img; //--------------
	char		**map;

	int			bit;
	int			line_size;
	int			type;

	t_img		textures[4]; // 0:North, 1:South, 2:West, 3:East
}	t_game;


int		close_window(t_game *game);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_player *player);
// int		key_handler(int keycode, t_game *game);

void	move_player(t_game *game);
void	init_player(t_player *player);

bool	touch(float px, float py, t_game *game);

float	distance(float x, float y);

char	**get_map(void);
int		raycasting(t_game *game);


void			load_texture(t_game *game, int index, char *path);
unsigned int	get_pixel_color(t_img *tex, int x, int y);
bool			touch(float px, float py, t_game *game);
void			put_pixel(int x, int y, int color, t_game *game);
void			draw_square(int x, int y, int size, int color, t_game *game);
void			clear_player(t_game *game);
void			create_map(t_game *game);


void	free_all(t_game *game);


#endif
