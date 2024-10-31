/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:20:44 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/09 19:49:31 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
PARSING LOGIC:
(0) Quick file-check for correct extension and readable file.
(1) Using get_next_line2, we open and read the file a first time to add
	the textures, colors and the map dimensions in a t_game structure.
	ALL texture and color formatting errors are handled here:
		- Correct identifiers for textures and colors.
		- Openable paths for textures.
		- Correct formatting for colors (r,g,b with 0 <= (r,g,b) <= 255).
		- Empty lines between every type of element are ok.
		- Textures and colors can be listed then read in any order.
		- Spaces between each element's information are ok.
		- No repeated identifiers.
		- No missing elements.
		- No unkown identifiers or elements.
		- Textures and colors must come before the map content.
	The following map specifics are checked:
		- Lines between the textures/colors and game map are empty.
		- Map content consists of only {0,1,N,S,W,E} or spaces.
		- There is only one player.
		- No empty lines within the map content.
		- No unknown element(s) found in the map.
	If an error is found before the end of file, everything is destroyed,
	the file is closed, and the program stops here.
	If no error is found after the end of file, we close the file.
(2) After finding the map dimensions in (1), we can allocate the right amount 
	of memory for the map.
	Using get_next_line2, we open and read the file a second time to add
	the map content in the t_game structure.
	We close the file.
(3) Once the map content has been added, we can check if the map is playable.
	Flood-filling.
*/

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
	new->player = NULL;
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
	if (game->player)
		free(game->player);
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
add_textures_and_colors: uses get_next_line2 until all colors and textures
have been added or upon error.
For each non-empty line, it uses check_id then adds the color or texture
using check_add_texture and check_add_color (see above).
Each non-empty line is temporarily stored in game->line in order to free
it upon error or when a new line is read.
*/
void	add_textures_and_colors(int fd, t_game *game)
{
	int		n_added;

	n_added = 0;
	game->line = get_next_line2(fd, game);
	while (game->line)
	{
		if (*(game->line) != '\n')
		{
			check_id(game, trim_spaces(game->line));
			check_add_texture(game, trim_spaces(game->line));
			check_add_color(game, trim_spaces(game->line));
			++n_added;
		}
		free(game->line);
		game->line = NULL;
		if (n_added == N_COLORS + N_TEXTURES)
			break ;
		game->line = get_next_line2(fd, game);
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
	add_map_content(argv[1], game);
	flood_fill(game, game->player->pos_x, game->player->pos_y);
	return (game);
}
