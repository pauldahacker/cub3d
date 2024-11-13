/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:17:57 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/13 19:08:45 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define BUFFER_SIZE 42

# define MAP_EXTENSION ".cub"
# define N_TEXTURES 4
# define N_COLORS 2
# define NO_COLOR -1
# define NO_DIRECTION 0

# define VISITED 'V'

// int			n_cols;//vertical
// int			n_rows;//horizontal
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
	int			n_cols;
	int			n_rows;
	t_player	*player;
}				t_game;

// parsing/checking.c
int		is_space(int c);
int		can_open(char *file);
int		is_format(char *str, char *ext);
void	check_id(t_game *game, char *str);
void	check_args(int argc, char **argv);

// parsing/gnl2.c
char	*get_next_line2(int fd, t_game *game);

// parsing/map_parsing_utils.c
int		is_valid_row(char *row);
void	check_row(char *row, t_game *game);
void	rowcpy(t_game *game, char *dest);

// parsing/map_parsing.c
void	init_player_angles(t_player *player, char direction);
void	find_map_dim(int fd, t_game *game);
void	add_map_content(char *file, t_game *game);
void	flood_fill(t_game *game, int x, int y);

// parsing/parsing_utils.c
char	*trim_spaces(char *str);
int		return_rgb(char *line);
void	check_add_color(t_game *game, char *line);
void	check_add_texture(t_game *game, char *line);

// parsing/parsing.c
t_game	*init_game(void);
void	destroy_game(t_game *game);
void	handle_error(t_game *game, char *err);
t_game	*parse(int argc, char **argv);

#endif
