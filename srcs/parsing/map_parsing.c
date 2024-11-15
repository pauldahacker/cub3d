/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:17:10 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/15 21:15:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
init_player_angles: sets the player's initial angles in degrees.
*/
void	init_player_angles(t_player *player, char direction)
{
	if (direction == 'N')
		player->middle_fov_angle = 90;
	else if (direction == 'W')
		player->middle_fov_angle = 180;
	else if (direction == 'S')
		player->middle_fov_angle = 270;
	else
		player->middle_fov_angle = 0;
	player->angle_start = player->middle_fov_angle + 30;
	player->angle_end = player->middle_fov_angle - 30;
	if (player->angle_end < 0)
		player->angle_end += 360;
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
		if ((int)ft_strlen(game->line) - 1 > game->n_cols)
			game->n_cols = ft_strlen(game->line) - 1;
		free(game->line);
		game->line = get_next_line2(fd, game);
	}
	close(fd);
	if (!game->n_rows)
		handle_error(game, "Error\nNo map content\n");
	if (!game->player)
		handle_error(game, "Error\nMap is missing a player\n");
}

static void	init_map_content(t_game *game)
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

/*
flood_fill: uses a recursive flood filling algorithm to check the map.
Starting at the player position, it marks the current element in the map
as VISITED if it is not a wall and not already visited.
Then it moves north, south, east and west and repeats.
If the current position is a wall, return.
If the current position is at the border and is a floor, the map is not closed.
*/
void	flood_fill(t_game *game, int x, int y)
{
	if (((game->map)[y])[x] == '0')
	{
		if (x == 0 || y == 0 || x == game->n_cols || y == game->n_rows)
			handle_error(game, "Error\nMap is not closed\n");
		game->map[y][x] = VISITED;
		flood_fill(game, x, y - 1);
		flood_fill(game, x, y + 1);
		flood_fill(game, x - 1, y);
		flood_fill(game, x + 1, y);
	}
	return ;
}
