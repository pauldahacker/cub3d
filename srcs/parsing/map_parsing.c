/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:55:54 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/09 19:49:14 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_valid_element(char c)
{
	return (is_space(c) || c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

int	is_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

/*
is_valid_row: takes a line and checks if it is a valid map row.
If it consists of anything other than '0', '1', 'N', 'S', 'W', 'E', or spaces,
it is invalid.
If it is empty (only spaces), it is invalid.
Else it is valid.
*/
int	is_valid_row(char *row)
{
	while (is_space(*row))
		++row;
	if (*row == '\0')
		return (0);
	while (*row && is_valid_element(*row))
		++row;
	return (!*row);
}

/*
check_row: does the same checks as is_valid_row, also checking for player.
It exits and displays a descriptive message in case of error (see handle_error).
It checks if there is one and only one player in the map, plus the correct
elements in the map.
*/
void	check_row(char *row, t_game *game)
{
	int	i;

	i = 0;
	while (is_space(row[i]))
		++i;
	if (row[i] == '\0')
		handle_error(game, "Error\nEmpty line in map content\n");
	while (row[i] && is_valid_element(row[i]))
	{
		if (is_direction(row[i]))
		{
			if (game->player != NULL)
				handle_error(game, "Error\nMore than one player in map\n");
			game->player = (t_player *)malloc(sizeof(t_player));
			if (!game->player)
				handle_error(game, "Error\nMalloc Error\n");
			game->player->pos_x = i;
			game->player->pos_y = game->n_rows;
			game->player->direction = row[i];
		}
		++i;
	}
	if (row[i])
		handle_error(game, "Error\nMap has unkown element(s)\n");
}

/*
find_map_dim: stores the game map dimensions in the t_game struct.
it takes the fd from add_textures_and_colors, then closes it.
uses get_next_line2 to go through the game map and checks for errors:
- it checks that the lines between the textures/colors and game map are empty
- it checks that the lines within the map content consist of only 
{0,1,N,S,W,E} or spaces.
- it checks that there is only one player.
- it checks that there are no empty lines within the map content

game->n_rows = number of lines we read from start to finish of the game map.
game->n_cols = the maximum length of the lines we read from start to finish
of the game map.
*/
void	find_map_dim(int fd, t_game *game)
{
	game->line = get_next_line2(fd, game);
	while (game->line && *game->line == '\n')
	{
		free(game->line);
		game->line = get_next_line2(fd, game);
	}
	while (game->line)
	{
		check_row(game->line, game);
		++(game->n_rows);
		if ((int)ft_strlen(game->line) > game->n_cols)
			game->n_cols = ft_strlen(game->line);
		free(game->line);
		game->line = get_next_line2(fd, game);
	}
	close(fd);
	if (!game->n_rows)
		handle_error(game, "Error\nNo map content\n");
	if (!game->player)
		handle_error(game, "Error\nMap is missing a player\n");
}

void	init_map_content(t_game *game)
{
	int	i;

	game->map = (char **)malloc((game->n_rows + 1) * (sizeof(char *)));
	if (!game->map)
		handle_error(game, "Error\nMalloc Error\n");
	i = -1;
	while (++i < game->n_rows)
	{
		game->map[i] = (char *)malloc((game->n_cols + 1) * (sizeof(char)));
		if (!game->map[i])
			handle_error(game, "Error\nMalloc Error\n");
	}
	game->map[i] = NULL;
}

void	rowcpy(t_game *game, char *dest)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(game->line))
	{
		if (is_space(game->line[i]))
			dest[i] = '1';
		else if (is_direction(game->line[i]))
			dest[i] = '0';
		else
			dest[i] = game->line[i];
	}
	while (i < game->n_cols)
		dest[i++] = '1';
	dest[i] = '\0';
}

void	print_map_content(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i] != NULL)	
	{
		printf("%s\n", game->map[i]);
		++i;
	}
}

void	add_map_content(char *file, t_game *game)
{
	int	fd;
	int	i;

	init_map_content(game);
	fd = open(file, O_RDONLY);
	game->line = get_next_line2(fd, game);
	while (!is_valid_row(game->line))
	{
		free(game->line);
		game->line = get_next_line2(fd, game);
	}
	i = 0;
	while (game->line)
	{
		rowcpy(game, game->map[i++]);
		free(game->line);
		game->line = get_next_line2(fd, game);
	}
	game->map[i] = NULL;
}

int	is_border(t_game *game, int x, int y)
{
	return (x == 0 || y == 0 || x == game->n_cols || y == game->n_rows);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (((game->map)[y])[x] == '0')
	{
		if (is_border(game, x, y))
			handle_error(game, "Error\nMap is not closed\n");
		game->map[y][x] = VISITED;
		flood_fill(game, x, y - 1);
		flood_fill(game, x, y + 1);
		flood_fill(game, x - 1, y);
		flood_fill(game, x + 1, y);
	}
	return ;
}