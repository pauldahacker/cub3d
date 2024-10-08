/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:20:44 by pde-masc          #+#    #+#             */
/*   Updated: 2024/09/30 13:20:48 by pde-masc         ###   ########.fr       */
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
		handle_error(NULL, "Malloc Error\n");
	new->line = NULL;
	new->stash = NULL;
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
destroy_game: frees game.
*/
void	destroy_game(t_game *game)
{
	int	i;

	if (game->line)
		free(game->line);
	if (game->stash)
		free(game->stash);
	if (game->north_path)
		free(game->north_path);
	if (game->south_path)
		free(game->south_path);
	if (game->west_path)
		free(game->west_path);
	if (game->east_path)
		free(game->east_path);
	i = -1;
	if (game->map)
	{
		while (++i < game->n_rows)
			free((game->map)[i]);
		free(game->map);
	}
	free(game);
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

	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return ;
	i = 3;
	while (line[i] && is_space(line[i]))
		++i;
	path = ft_strdup(line + i);
	if (!path)
		handle_error(game, "Malloc Error\n");
	if (!ft_strncmp(line, "NO ", 3) && !game->north_path)
		game->north_path = path;
	else if (!ft_strncmp(line, "SO ", 3) && !game->south_path)
		game->south_path = path;
	else if (!ft_strncmp(line, "WE ", 3) && !game->west_path)
		game->west_path = path;
	else if (!ft_strncmp(line, "EA ", 3) && !game->east_path)
		game->east_path = path;
	else
	{
		free(path);
		handle_error(game, "Error\nTexture id(s) defined more than once\n");
	}
}

/*
check_add_color: checks line for errors and adds it as a color to t_game.
It should always be used after check_id (see check_id in checking.c).
It checks if the line is properly formatted (see return_rgb in parsing_utils.c)
If not, it exits and prints a descriptive error using handle_error.
*/
void	check_add_color(t_game *game, char *line)
{
	if (ft_strncmp(line, "F ", 2) && ft_strncmp(line, "C ", 2))
		return ;
	if (!ft_strncmp(line, "F ", 2) && game->floor_color == NO_COLOR)
	{
		if (return_rgb(line + 2) == NO_COLOR)
			handle_error(game, "Error\nIncorrect color format\n");
		game->floor_color = return_rgb(line + 2);
	}
	else if (!ft_strncmp(line, "C ", 2) && game->ceiling_color == NO_COLOR)
	{
		if (return_rgb(line + 2) == NO_COLOR)
			handle_error(game, "Error\nIncorrect color format\n");
		game->ceiling_color = return_rgb(line + 2);
	}
	else
		handle_error(game, "Error\nColor defined more than once\n");
}

/*
add_textures_and_colors: uses get_next_line until all colors and textures
have been added or upon error.
For each non-empty line, it uses check_id then adds the color or texture
using check_add_texture and check_add_color (see above).
*/
void	add_textures_and_colors(int fd, t_game *game)
{
	int		n_added;

	n_added = 0;
	game->line = get_next_line(fd, game);
	while (game->line)
	{
		if (*(game->line) != '\n')
		{
			check_id(game, trim_spaces(game->line));
			check_add_texture(game, trim_spaces(game->line));
			check_add_color(game, game->line);
			++n_added;
		}
		free(game->line);
		if (n_added == N_COLORS + N_TEXTURES)
			break ;
		game->line = get_next_line(fd, game);
	}
	if (game->ceiling_color == NO_COLOR || game->floor_color == NO_COLOR)
		handle_error(game, "Error\nMap has missing color\n");
	if (!game->north_path || !game->south_path
		|| !game->west_path || !game->east_path)
		handle_error(game, "Error\nMap has missing texture\n");
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
	printf("---------GAME INFO---------\n");
	printf("NORTH: %s\n", game->north_path);
	printf("SOUTH: %s\n", game->south_path);
	printf("WEST: %s\n", game->west_path);
	printf("EAST: %s\n", game->east_path);
	printf("FLOOR COLOR: %d\n", game->floor_color);
	printf("CEILING COLOR: %d\n", game->ceiling_color);
	printf("N_ROWS: %d\n", game->n_rows);
	printf("N_COLS: %d\n", game->n_cols);
	printf("---------------------------\n");
	return (game);
}
