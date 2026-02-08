/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:50:27 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/09 05:46:11 by sohyamaz         ###   ########.fr       */
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
# include <fcntl.h>
# include "mlx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define SPEED 0.5
# define DIRE_SPEED 0.01

# define MM_RAD 5
# define MM_PLAYER_X 20
# define MM_PLAYER_Y 20
# define MM_PLAYER_COLOR 0xFF0000

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

# define HEIGHT 720
# define WIDTH 1280

/* === GAME CONSTANTS === */

# define WALL 16
# define PI 3.14159265358979323

/* === MAP CONSTANTS === */

# ifndef NORTH
#  define NORTH "NO "
# endif

# ifndef EAST
#  define EAST "EA "
# endif

# ifndef SOUTH
#  define SOUTH "SO "
# endif

# ifndef WEST
#  define WEST "WE "
# endif

# ifndef FLOOR
#  define FLOOR "F "
# endif

# ifndef CEILING
#  define CEILING "C "
# endif

/* === STRUCTURES FOR RAYCAST=== */

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}	t_square;

typedef struct s_color
{
	int	ceil;
	int	floor;
}	t_color;

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

typedef struct s_vector
{
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
}	t_vector;

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
	int			tex_x;
}	t_ray;

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

/* === STRUCTURES FOR PARSE=== */
typedef struct s_color	t_color;
typedef struct s_config	t_config;
typedef struct s_map	t_map;
typedef struct s_board	t_board;

struct s_color
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
} ;

struct s_config
{
	char	*no_path;
	char	*ea_path;
	char	*so_path;
	char	*we_path;
	t_color	*f_color;
	t_color	*c_color;
} ;

struct s_board
{
	char	**sheet;
	int		sheet_x;
	int		sheet_y;
} ;

struct s_map
{
	int			cubfd;
	size_t		x;
	size_t		y;
	int			user_x;
	int			user_y;
	t_config	config;
	char		**mapdata;
} ;

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

void			draw_texture(t_game *game, t_ray *ray, int x, t_color colorcf);
int				get_line_len(char *line);
int				get_map_height(char **map);
int				is_in_map(t_game *game, int x, int y);
int				is_wall(t_game *game, int x, int y);
void			draw_minimap_wall(t_game *game, int x, int y);
unsigned int	apply_shading(unsigned int color, double distance);
void			draw_texture_column( t_game *game, t_ray *ray, \
									int x, t_color c);

/* --- parse.c --- */
bool			parse(int argc, char **argv, t_map *map);
/* --- parse_closed_map.c --- */
bool			is_map_closed(t_map *map);
/* --- parse_color_code.c --- */
bool			set_valid_color_code(t_config *config, char *line);
/* --- parse_map_contents.c --- */
bool			parse_map_contents(t_map *map);
/* --- parse_map_data.c --- */
bool			parse_map_data(t_map *map);
/* --- parse_map_util.c --- */
void			free_sheet(char **sheet);
bool			is_user(char c);
char			**get_big_sheet(t_map *map);
/* --- parse_texture_file.c --- */
bool			set_valid_texture_path(t_config *config, char *line);
/* --- parse_util.c --- */
bool			is_valid_extention(char *fullpath, char *target);
char			*get_next_line(int fd);

#endif
