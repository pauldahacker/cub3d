/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:20:44 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/08 17:15:17 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
init_game: allocates memory for t_game and sets its elements to initial values.
*/
t_game	*init_game(void)
{
	t_game	*new;

	new = (t_game *)malloc(sizeof(t_game));
	if (!new)
		handle_error("Malloc Error\n");
	new->north_path = NULL;
	new->south_path = NULL;
	new->west_path = NULL;
	new->east_path = NULL;
	new->floor_color = NO_COLOR;
	new->ceiling_color = NO_COLOR;
	new->map = NULL;
	new->n_rows = 0;
	new->n_cols = 0;
	return (new);
}

/*
check_add_texture: checks line for errors and adds it as a texture to t_game.
It should always be used after check_id (see check_id in checking.c).
It checks if the line is properly formatted, and if the path exists.
If not, it exits and prints a descriptive error using handle_error.
*/
void	check_add_texture(t_game *game, char *line)
{
	int		i;
	char	*path;

	while (is_space(*line))
		++line;
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return ;
	i = 3;
	while (line[i] && is_space(line[i]))
		++i;
	path = ft_strdup(line + i);
	if (!path)
		handle_error("Malloc Error\n");
	if (!ft_strncmp(line, "NO ", 3) && !game->north_path)
		game->north_path = path;
	else if (!ft_strncmp(line, "SO ", 3) && !game->south_path)
		game->south_path = path;
	else if (!ft_strncmp(line, "WE ", 3) && !game->west_path)
		game->west_path = path;
	else if (!ft_strncmp(line, "EA ", 3) && !game->east_path)
		game->east_path = path;
	else
		handle_error("Error\nTexture identifier(s) defined more than once\n");
}

/*
check_add_color: checks line for errors and adds it as a color to t_game.
It should always be used after check_id (see check_id in checking.c).
It checks if the line is properly formatted (see return_rgb in parsing_utils.c)
If not, it exits and prints a descriptive error using handle_error.
*/
void	check_add_color(t_game *game, char *line)
{
	while (is_space(*line))
		++line;
	if (ft_strncmp(line, "F ", 2) && ft_strncmp(line, "C ", 2))
		return ;
	if (!ft_strncmp(line, "F ", 2) && game->floor_color == NO_COLOR)
		game->floor_color = return_rgb(line + 2);
	else if (!ft_strncmp(line, "C ", 2) && game->ceiling_color == NO_COLOR)
		game->ceiling_color = return_rgb(line + 2);
	else
		handle_error("Error\nCeiling or floor color defined more than once\n");
}

/*
add_textures_and_colors: uses get_next_line until all colors and textures
have been added or upon error.
For each non-empty line, it uses check_id then adds the color or texture
using check_add_texture and check_add_color (see above).
*/
void	add_textures_and_colors(int fd, t_game *game)
{
	char	*line;
	int		n_added;

	n_added = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n')
		{
			check_id(trim_end_spaces(line));
			check_add_texture(game, trim_end_spaces(line));
			check_add_color(game, line);
			++n_added;
		}
		free(line);
		if (n_added == N_COLORS + N_TEXTURES)
			break ;
		line = get_next_line(fd);
	}
	if (game->ceiling_color == NO_COLOR || game->floor_color == NO_COLOR)
		handle_error("Error\nMap has missing color\n");
	if (!game->north_path || !game->south_path
		|| !game->west_path || !game->east_path)
		handle_error("Error\nMap has missing texture\n");
}

/*
parse: if no issues detected in input, it creates a t_game structure with:
- north, south, west and east textures' respective paths.
- floor and ceiling respective colors.
- the game map as a (char **) array
- the game map dimensions (n_rows, n_cols)
if an issue is detected, it exits and prints a descriptive error.
*/
t_game	*parse(int argc, char **argv)
{
	int		fd;
	t_game	*game;

	check_args(argc, argv);
	game = init_game();
	fd = open(argv[1], O_RDONLY);
	add_textures_and_colors(fd, game);
	find_map_dim(fd, game);
/*	printf("---------GAME INFO---------\n");
	printf("NORTH: %s\n", game->north_path);
	printf("SOUTH: %s\n", game->south_path);
	printf("WEST: %s\n", game->west_path);
	printf("EAST: %s\n", game->east_path);
	printf("FLOOR COLOR: %d\n", game->floor_color);
	printf("CEILING COLOR: %d\n", game->ceiling_color);
	printf("N_ROWS: %d\n", game->n_rows);
	printf("N_COLS: %d\n", game->n_cols);
	printf("---------------------------\n");*/
	return (game);
}
