/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:18:15 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/14 19:49:08 by simarcha         ###   ########.fr       */
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
# define WINDOW_X		1600
# define WINDOW_Y		900
# define SHADE			0.6
# define MINI_START_X	5
# define MINI_START_Y	5

# define MOVEMENT_SPEED 8
# define ROTATE_SPEED 	5

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

// Colors
# define STANDARD_GREY		0x808080
# define DARK_GREY			0x404040
# define CLEAR_GREY			0x999999
# define SILVER_GREY		0x909090
# define BLACK				0x000000
# define WHITE				0xFFFFFF
# define BLUE				0x0000FF
# define YELLOW				0xFFFF00
# define SKY_BLUE			0xADD8E6
# define ELECTRIC_BLUE		0x7df9ff
# define BROWN				0x964B00

//maths
# define PI					3.14159265358979323846

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

// typedef struct raycasting
// {
// 	double		pos_x;//player position in abscissa. The unit are the pixels!
// 	double		pos_y;//player position in ordinate. The unit are the pixels!
// 	double		angle_start;//starting angle from our FOV
// 	double		angle_end;//ending angle from our FOV
// 	double		middle_fov_angle;//middle angle between angle_start & angle_end
// 	double		ray_angle;//angle of the current ray drawn
// 	double		subsequent_angle;//degrees variations between 2 rays
// 	bool		horizontal_distance_chosen;//or horizontal or vertical distance
// 	t_proj		proj_plan;
// 	t_block		point_hit;
// 	double		projected_wall_height;
// 	double		distance_to_wall;
// 	double		wall_height_in_px;
// 	double		horizontal_wall_size_in_px;
// }	t_player;

typedef struct raycasting
{
	double		pos_x;
	double		pos_y;
	double		angle_start;
	double		angle_end;
	double		middle_fov_angle;
	double		ray_angle;
	double		subsequent_angle;
	bool		horizontal_distance_chosen;
	t_proj		proj_plan;
	t_block		point_hit;
	double		projected_wall_height;
	double		distance_to_wall;
	double		horizontal_wall_size_in_px;
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

typedef struct textures
{
	char			*path;
	void			*img;
	int				width;
	int				height;
	int				endian;
	int				bpp;
	int				size_line;
	unsigned char	*data;
}				t_texture;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		data;
	t_game		*game;
	t_texture	north_tex;
	t_texture	south_tex;
	t_texture	west_tex;
	t_texture	east_tex;
	t_keys		keys;
}				t_vars;

// controls/controls.c
int			on_destroy(t_vars *vars);
int			on_keypress(int keysym, t_vars *vars);
int			on_keyrelease(int keysym, t_vars *vars);
int			update_player(t_vars *vars);

// minimap/minimap_utils.c
void		draw_fov_line(t_vars vars, t_block *p1, t_block *p2);
int			add_shade(double opacity, int color);

// minimap/minimap.c
void		draw_minimap(t_vars *vars, t_game *game);

// controls/movement_utils.c
double		return_x_increment(t_vars *vars, double angle, int speed);
double		return_y_increment(t_vars *vars, double angle, int speed);

// controls/movement.c
int			on_move_up(t_vars *vars, int speed);
int			on_move_down(t_vars *vars, int speed);
int			on_move_left(t_vars *vars, int speed);
int			on_move_right(t_vars *vars, int speed);

// controls/rotation.c
double		increment_angle(double angle, double to_add);
int			on_rotate_left(t_vars *vars, int attempted_speed);
int			on_rotate_right(t_vars *vars, int attempted_speed);

// controls/controls.c
int			on_destroy(t_vars *vars);
int			on_keypress(int keysym, t_vars *vars);

//srcs/textures/draw_textures.c
void		draw_wall(t_vars *vars, int *x, int *y);

//main.c
void		my_mlx_pixel_put(t_vars vars, int x, int y, int color);
void		draw_minimap(t_vars *vars, t_game *game);

#endif
