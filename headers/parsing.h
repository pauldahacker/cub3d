/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:17:57 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/10 12:28:45 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 42
# endif

# define MAP_EXTENSION ".cub"
# define N_TEXTURES 4
# define N_COLORS 2
# define NO_COLOR -1
# define NO_DIRECTION 0

# define VISITED 'V'

typedef struct s_game
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
	int			n_cols;//vertical
	int			n_rows;//horizontal
	t_player	*player;
}				t_game;

// parsing/gnl2.c
char	*get_next_line2(int fd, t_game *game);

// parsing/checking.c
void	check_id(t_game *game, char *str);
int		can_open(char *file);
int		is_format(char *str, char *ext);
void	handle_error(t_game *game, char *err);
void	check_args(int argc, char **argv);

// parsing/map_parsing.c
void	print_map_content(t_game *game);
void	find_map_dim(int fd, t_game *game);
void	add_map_content(char *file, t_game *game);
void	flood_fill(t_game *game, int x, int y);

// parsing/parsing_utils.c
int			is_space(int c);
char		*trim_spaces(char *str);
int			return_rgb(char *line);

// parsing/parsing.c
void		destroy_game(t_game *game);
t_game		*parse(int argc, char **argv);

//parsing/fd_into_array.c
char	**fd_into_array(char *argv_1);
void	free_array(char **array);

//parsing/fd_into_array.c
char	**fd_into_array(char *argv_1);
void	free_array(char **array);

#endif
