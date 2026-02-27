/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:50:27 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/23 20:04:08 by atashiro         ###   ########.fr       */
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
# include <stddef.h>
# include <limits.h>
# include <stdint.h>
# include "mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
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

/* === STRUCTURES definition=== */
typedef struct s_rgb	t_rgb;
typedef struct s_config	t_config;
typedef struct s_map	t_map;
typedef struct s_board	t_board;
typedef struct s_square	t_square;
typedef struct s_color	t_color;
typedef struct s_player	t_player;
typedef struct s_vector	t_vector;
typedef struct s_ray	t_ray;
typedef struct s_img	t_img;
typedef struct s_game	t_game;

/* === STRUCTURES FOR PARSE=== */
struct s_rgb
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	is_configured;
} ;

struct s_config
{
	char	*no_path;
	char	*ea_path;
	char	*so_path;
	char	*we_path;
	t_rgb	f_color;
	t_rgb	c_color;
} ;

struct s_board
{
	char	**sheet;
	int		sheet_x;
	int		sheet_y;
	int		dest_x[4];
	int		dest_y[4];
} ;

struct s_map
{
	int			cubfd;
	size_t		config_line;
	size_t		x;
	size_t		y;
	int			user_x;
	int			user_y;
	int			user;
	double		dire;
	t_config	config;
	char		**mapdata;
} ;

/* === STRUCTURES FOR RAYCAST=== */

struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
} ;

struct s_color
{
	int	ceil;
	int	floor;
} ;

struct s_player
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
} ;

struct s_vector
{
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		pos_x;
	double		pos_y;
} ;

struct s_ray
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
} ;

struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
} ;

struct s_game
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
	t_config	*config;
	t_img		textures[4]; // 0:North, 1:South, 2:West, 3:East
} ;

/* === FUNCTIONS === */
/* --- apply_shading.c --- */
unsigned int	apply_shading(unsigned int color, double distance);
/* --- calc_move.c --- */
void			calc_move_delta(t_player *p, float *add_x, float *add_y);
/* --- calc_texture.c --- */
void			draw_texture_column(t_game *game, t_ray *ray, int x, t_color c);
/* --- calc_wall_height.c --- */
void			calc_wall_height(t_ray *ray);
/* --- dda.c --- */
void			perform_dda(t_game *game, t_ray *ray);
/* --- dup_parsed_arguments.c --- */
char			**get_parsed_map(t_map *map);
t_config		*get_parsed_config(t_config *config);
/* --- init_map.c --- */
t_map			*init_map(int argc, char **argv);
/* --- init_player.c --- */
void			init_player(t_player *player, t_map *map);
/* --- init_raycast.c --- */
void			init_ray(t_ray *ray, t_vector *vec, int x);
/* --- key.c --- */
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
/* --- load_texture.c --- */
bool			set_wall_texture(t_game *game);
/* --- minimap.c --- */
void			draw_square(t_game *game, t_square square);
void			create_map(t_game *game);
/* --- move.c --- */
void			move_player(t_game *game);
/* --- parse.c --- */
bool			parse(t_map *map, char *path);
/* --- parse_closed_map.c --- */
bool			is_map_closed(t_map *map);
/* --- parse_color_code.c --- */
bool			set_valid_color_code(t_config *config, char *line);
/* --- parse_config_informations.c --- */
bool			parse_config_informations(t_map *map);
/* --- parse_map_data.c --- */
bool			parse_map_data(t_map *map);
/* --- parse_texture_file.c --- */
bool			set_valid_texture_path(t_config *config, char *line);
/* --- print_config_error.c --- */
void			print_invalid_wall(void);
void			print_invalid_color(void);
void			print_unexpected_char(void);
void			print_dup_config_err(void);
/* --- print_error.c --- */
void			print_prefix(void);
void			print_invalid_extention(void);
/* --- print_init_error.c --- */
void			print_arg_error(void);
void			print_lack_of_config(void);
void			print_nomap_error(void);
void			print_too_big_map(void);
/* --- print_mapdata_error.c --- */
void			print_invalid_symbol(void);
void			print_player_error(int player);
void			print_torned_floor(void);
void			print_wall_error(char c);
/* --- raycasting.c --- */
int				raycasting(t_game *game);
/* --- texture.c --- */
void			draw_texture(t_game *game, t_ray *ray, int x, t_color colorcf);
/* --- utils_for_allocation.c --- */
void			*ft_calloc(size_t nmemb, size_t size);
size_t			ft_strlen(const char *s);
void			ft_bzero(void *s, size_t n);
/* --- utils_for_duplication.c --- */
char			*ft_substr(char const *s, unsigned int start, size_t len);
size_t			ft_strlcpy(char *dest, const char *src, size_t len);
char			*ft_strdup(const char *s);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
/* --- utils_for_free.c --- */
void			free_duplicated_data(t_game *game);
void			free_pathes(t_config *config);
void			free_mapdata(char **map);
void			free_args(t_map *map);
void			free_all(t_game *game);
/* --- utils_for_game.c --- */
int				close_window(t_game *game);
unsigned int	get_pixel_color(t_img *tex, int x, int y);
bool			touch(float px, float py, t_game *game);
void			put_pixel(int x, int y, int color, t_game *game);
void			clear_player(t_game *game);
/* --- utils_for_minimap.c --- */
int				get_line_len(char *line);
int				get_map_height(char **map);
int				is_in_map(t_game *game, int x, int y);
int				is_wall(t_game *game, int x, int y);
void			draw_minimap_wall(t_game *game, int x, int y);
/* --- utils_for_parsing.c --- */
bool			is_valid_extention(char *fullpath, char *target);
char			*ft_strrchr(const char *str, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
/* --- utils_for_parsing_map.c --- */
void			free_sheet(char **sheet);
bool			is_user(char c);
double			set_dire(char dire);
char			**get_big_sheet(t_map *map);
/* --- utils_for_read.c --- */
bool			is_config_line(char c);
char			*get_next_line(int fd);

#endif
