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

# define MINIMAP_SHADE	0.65
# define MINIMAP_HEIGHT WINDOW_Y / 4
# define MINIMAP_LENGTH WINDOW_X / 4
# define MINIMAP_START_X 5
# define MINIMAP_START_Y 5

# define MOVEMENT_SPEED 8
# define ROTATE_SPEED 3

// MLX
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_DESTROY		17

# define KEY_PRESS_MASK			1L<<0
# define KEY_RELEASE_MASK		1L<<1
# define NO_MASK				0


// Keys
# ifdef __linux__
#  define ESC 65307
#  define W 119
#  define A 97
#  define S 115
#  define D 100
#  define LEFT 65361
#  define RIGHT 65363

# elif defined(__APPLE__)
#  define ESC 53
#  define W 13
#  define A 0
#  define S 1
#  define D 2
#  define LEFT 123
#  define RIGHT 124
# endif

//maths
# define PI 	3.14159265358979323846
typedef struct s_game t_game;

/*typedef struct s_game
{
	char		*line;
	char		*stash;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			n_cols;
	int			n_rows;
	t_player	*player;
}				t_game;*/

typedef struct s_keys {
	int w;
	int a;
	int s;
	int d;
	int left;
	int right;
}	t_keys;
typedef struct raycasting
{
	double		pos_x;//⭐//player position in abscissa. The unit are the pixels!
	double		pos_y;//⭐//player position in ordinate. The unit are the pixels!
	double		angle;//⭐//angle (in degrees) of our ray starting from the abscissa axis 0 ≤ angle ≤360
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
}				t_vars;

// controls/controls.c
int	on_destroy(t_vars *vars);
int	on_keypress(int keysym, t_vars *vars);
int	on_keyrelease(int keysym, t_vars *vars);
int	update_player(t_vars *vars);

// minimap/minimap_utils.c
void	draw_fov_line(t_vars vars, t_point *p1, t_point *p2);
int		add_shade(double opacity, int color);

// minimap/minimap.c
void	draw_minimap(t_vars *vars, t_game *game);

// controls/movement_utils.c
double  return_x_increment(t_vars *vars, double angle, int attempted_speed);
double  return_y_increment(t_vars *vars, double angle, int attempted_speed);

// controls/movement.c
int	on_move_up(t_vars *vars, int attempted_speed);
int	on_move_down(t_vars *vars, int attempted_speed);
int	on_move_left(t_vars *vars, int attempted_speed);
int	on_move_right(t_vars *vars, int attempted_speed);

// controls/rotation.c
double  increment_angle(double angle, double to_add);
int		on_rotate_left(t_vars *vars, int attempted_speed);
int		on_rotate_right(t_vars *vars, int attempted_speed);

//main.c
void		my_mlx_pixel_put(t_vars vars, int x, int y, int color);
void		draw_game(t_vars vars, t_game *game);
void		draw_wall(t_vars *vars, double projected_wall_height, int *x, int *y);

#endif
