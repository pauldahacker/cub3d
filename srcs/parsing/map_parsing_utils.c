/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:16:47 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/04 13:16:48 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_element(char c)
{
	return (is_space(c) || c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E');
}

static int	is_direction(char c)
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
			init_player_angles(game->player, row[i]);
		}
		++i;
	}
	if (row[i])
		handle_error(game, "Error\nMap has unkown element(s)\n");
}

void	rowcpy(t_game *game, char *dest)
{
	int	i;

	i = -1;
	while (++i < (int)ft_strlen(game->line) - 1)
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
