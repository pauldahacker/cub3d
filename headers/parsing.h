#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 42
# endif

# define MAP_EXTENSION ".cub"
# define N_TEXTURES 4
# define N_COLORS 2

typedef struct s_game
{
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
    int         floor_color;
    int         ceiling_color;
    char		**map;
}				t_game;



char	*get_next_line(int fd);

int     is_readable(char *file);
int     is_format(char *str, char *ext);
void	handle_error(char *str);
void	check_args(int argc, char **argv);

int         is_space(int c);
char        *trim_end_spaces(char *str);
int         return_rgb(char *line);
t_game    *buffer(int fd);

//parsing/fd_into_array.c
char	**fd_into_array(char *argv_1);
void	free_array(char **array);

#endif