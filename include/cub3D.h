/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:50:27 by atashiro          #+#    #+#             */
/*   Updated: 2026/01/29 16:21:09 by atashiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* === INCLUDES === */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "mlx/mlx.h"

# define SPEED 5

/* === KEY CODES === */

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307

/* === EVENT CODES === */

# define E_KEY_PRESS 2
# define E_WIN_RESIZE 9
# define E_WIN_CLOSE 17

/* === WINDOW SETTING === */

# define HIGHT 720
# define WIDTH 1280

/* === GAME CONSTANTS === */

# define WALL 16
# define PI 3.14159265358979323

/* === STRUCTURES === */

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

typedef struct s_player
{
	float		x;
	float		y;
	float		dire;
	bool		key_w;
	bool		key_s;
	bool		key_a;
	bool		key_d;
	bool		left_turn;
	bool		right_turn;
}	t_player;

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
}	t_ray;

typedef struct s_vector
{
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
}	t_vector;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	char		*data;
	void		*img;
	char		**map;
	int			bit;
	int			line_size;
	int			type;
	t_img		textures[4]; // 0:North, 1:South, 2:West, 3:East
}	t_game;

/* === FUNCTIONS === */
/* --- main.c --- */
unsigned int	get_pixel_color(t_img *tex, int x, int y);
bool			touch(float px, float py, t_game *game);
void			put_pixel(int x, int y, int color, t_game *game);
void			draw_square(t_game *game, t_square square);
void			clear_player(t_game *game);

/* --- get_map.c --- */
char			**get_map(void);

/* --- key.c --- */
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_player *player);

/* --- raycasting.c --- */

int				raycasting(t_game *game);

/* --- raycasting_utils.c --- */
float			distance(float x, float y);

/* --- load_texture.c --- */
void			load_texture(t_game *game, int index, char *path);
void			set_wall_texture(t_game *game);

/* --- utils.c --- */
int				close_window(t_game *game);

/* --- free.c --- */
void			free_map(char **map);
void			free_all(t_game *game);

/* --- move.c --- */
void			move_player(t_game *game);

/* --- move_calc.c --- */
void			calc_move_delta(t_player *player, float *add_x, float *add_y);

/* --- minimap.c --- */
void			create_map(t_game *game);

/* --- init_player.c --- */
void			init_player(t_player *player);

/* --- dda.c --- */
void			perform_dda(t_game *game, t_ray *ray);

/* --- calcurate_wall_height.c --- */
void			calc_wall_height(t_ray *ray);

/* --- init_raycast.c --- */
void			init_ray(t_ray *ray, t_vector *vec, int x);

#endif
