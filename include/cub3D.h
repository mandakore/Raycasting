/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 17:50:27 by atashiro          #+#    #+#             */
/*   Updated: 2025/11/03 03:03:08 by atashiro         ###   ########.fr       */
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

# define HIGHT 720
# define WIDTH 1280

# define WALL 42

# define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679



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
}	t_game;


int		close_window(t_game *game);

int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
// int		key_handler(int keycode, t_game *game);

void	move_player(t_player *player);
void	init_player(t_player *player);



#endif
