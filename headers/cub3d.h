/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:18:15 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/23 17:19:24 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __linux__
#  include "../mlx/mlx.h"

# elif defined(__APPLE__)
#  include "../mlx_macOS/mlx.h"
# endif

# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <stdbool.h>
# include <sys/uio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "colors.h"
# include "raycasting.h"
# include "parsing.h"
# include "textures.h"

// Configurations
# define WINDOW_X 1600
# define WINDOW_Y 900

# define SHADE	0.6
# define MINI_START_X 5
# define MINI_START_Y 5

# define MOVEMENT_SPEED 8
# define ROTATE_SPEED 3

// MLX EVENTS
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_DESTROY		17

// Keys
# ifdef __linux__
#  define ESC	65307
#  define W_KEY	119
#  define A_KEY	97
#  define S_KEY	115
#  define D_KEY	100
#  define LEFT	65361
#  define RIGHT	65363

# elif defined(__APPLE__)
#  define ESC	53
#  define W_KEY	13
#  define A_KEY	0
#  define S_KEY	1
#  define D_KEY	2
#  define LEFT	123
#  define RIGHT	124
# endif

//maths
# define PI 	3.14159265358979323846

typedef struct s_game	t_game;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;
typedef struct raycasting
{
	double		pos_x;//⭐//player position in abscissa. The unit are the pixels!
	double		pos_y;//⭐//player position in ordinate. The unit are the pixels!
	double		angle;//⭐//angle [0-360) of ray starting from abscissa axis
	char		direction;//will determine our FOV
	double		angle_start;//⭐
	double		angle_end;//⭐
	double		subsequent_angle;//⭐
	double		distance_to_wall;//the distance from the player to the wall
}	t_player;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	double		scale;
	int			center_x;
	int			center_y;
}				t_data;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		data;
	t_game		*game;
	t_keys		keys;
	void		*engine;
}				t_vars;

// controls/controls.c
int		on_destroy(t_vars *vars);
int		on_keypress(int keysym, t_vars *vars);
int		on_keyrelease(int keysym, t_vars *vars);
int		update_player(t_vars *vars);

// minimap/minimap_utils.c
void	draw_fov_line(t_vars vars, t_point *p1, t_point *p2);
int		add_shade(double opacity, int color);

// minimap/minimap.c
void	draw_minimap(t_vars *vars, t_game *game);

// controls/movement_utils.c
double	return_x_increment(t_vars *vars, double angle, int speed);
double	return_y_increment(t_vars *vars, double angle, int speed);

// controls/movement.c
int		on_move_up(t_vars *vars, int speed);
int		on_move_down(t_vars *vars, int speed);
int		on_move_left(t_vars *vars, int speed);
int		on_move_right(t_vars *vars, int speed);

// controls/rotation.c
double	increment_angle(double angle, double to_add);
int		on_rotate_left(t_vars *vars, int speed);
int		on_rotate_right(t_vars *vars, int speed);

//main.c
void	my_mlx_pixel_put(t_vars vars, int x, int y, int color);
void	draw_game(t_vars vars, t_game *game);
void	draw_wall(t_vars *vars, double projected_wall_height, int *x, int *y);

#endif
