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
# include <sys/uio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "textures.h"
# include "raycasting.h"

// Configurations
# define WINDOW_X 1600
# define WINDOW_Y 900

// Keys
# define ESC 65307

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
}				t_vars;

// Control functions
int	on_destroy(t_vars *vars);
int	on_keypress(int keysym, t_vars *vars);



#endif