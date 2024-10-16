/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:18:15 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/16 17:45:43 by simarcha         ###   ########.fr       */
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
# include "raycasting.h"
# include "parsing.h"
# include "textures.h"

// Configurations
# define WINDOW_X 1600
# define WINDOW_Y 900

# define MINIMAP_HEIGHT WINDOW_Y / 2
# define MINIMAP_LENGTH WINDOW_X / 2
# define MINIMAP_START_X 5
# define MINIMAP_START_Y 5

# define MOVEMENT_SPEED 10

// Keys
# define ESC 65307

// Colors
# define GREY				0x808080
# define BLACK				0x000000
# define WHITE				0xFFFFFF
# define BLUE		0x0000FF
# define YELLOW		0xFFFF00
# define SKY_BLUE	0xADD8E6
# define BLUE			0x0000FF
# define ELECTRIC_BLUE	0x7df9ff

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

typedef struct raycasting
{
	double		pos_x;//player position in abscissa. The unit are the pixels!
	double		pos_y;//player position in ordinate. The unit are the pixels!
	double		middle_angle;
	double		angle;//angle (in degrees) of our ray starting from the abscissa axis 0 ≤ angle ≤360
	char		direction;//will determine our FOV
	double		angle_start;
	double		angle_end;
	double		subsequent_angle;
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
}				t_vars;

// Control functions
int	on_destroy(t_vars *vars);
int	on_keypress(int keysym, t_vars *vars);

//main.c
void		my_mlx_pixel_put(t_vars vars, int x, int y, int color);
void		draw_game(t_vars vars, t_game *game);
void		draw_wall(t_vars *vars, double projected_wall_height, int *x, int *y);

void		draw_minimap(t_vars *vars, t_game *game);

#endif
