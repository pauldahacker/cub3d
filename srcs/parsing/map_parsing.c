/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:55:54 by pde-masc          #+#    #+#             */
/*   Updated: 2024/09/30 17:55:57 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int is_valid_element(char c)
{
	return (is_space(c) || c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

int is_direction(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int is_valid_row(char *row)
{
	while (*row && is_valid_element(*row))
		++row;
	return (!*row);
}

/*
find_map_dim: stores the game map dimensions in the t_game struct.
it takes the fd from add_textures_and_colors, then closes it.
uses get_next_line to go through the game map and quickly checks for errors:
- it checks that the lines between the textures/colors and game map are empty
- it checks that the lines within the map content consist of only 
{0,1,N,S,W,E} or spaces.

game->n_rows = number of lines we read from start to finish of the game map.
game->n_cols = the maximum length of the lines we read from start to finish
of the game map.
*/
void	find_map_dim(int fd, t_game *game)
{
	char	*line;	

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && is_valid_row(line))
	{
		++(game->n_rows);
		if ((int)ft_strlen(line) > game->n_cols)
			game->n_cols = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (line && !is_valid_row(line))
		handle_error("Error\nMap has unknown element(s)\n");
	if (line)
		free(line);
}