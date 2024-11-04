/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:25:38 by pde-masc          #+#    #+#             */
/*   Updated: 2024/09/30 13:25:40 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
Returns str with starting and ending whitespaces removed.
e.g. "   \n  \tHello I am Paul  \n \t " --> "Hello I am Paul"
*/
char	*trim_spaces(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	while (is_space(str[--i]))
		str[i] = '\0';
	while (*str && is_space(*str))
		++str;
	return (str);
}

/*
is_color_format: helper function for return_rgb.
It checks that the r, g, or b in rgb is formatted as:
	- a 3-digit number;
	- can be surrounded by spaces and/or preceded by zeros;
	- has to be followed by [next_separator] which is either
		-> ',' for the r or g in rgb (first two)
		-> '\0' for the b in rgb (last)
If good format, returns 1, else returns 0.
*/
static int	is_color_format(char *line, char next_separator)
{
	int	i;

	i = 0;
	while (is_space(*line))
		++line;
	if (!ft_isdigit(*line))
		return (0);
	while (*line == '0')
		++line;
	while (ft_isdigit(*line) && i++ < 3)
		++line;
	while (is_space(*line))
		++line;
	return (*line == next_separator);
}

/*
Takes line, which should be formatted like this: "r,g,b"
Where r,g,b represent numbers in range [0,255].
Returns color in decimal form, or NO_COLOR (=-1) if not correctly formatted
(see is_color_format).
*/
int	return_rgb(char *line)
{
	int	r;
	int	g;
	int	b;

	if (!is_color_format(line, ','))
		return (NO_COLOR);
	r = ft_atoi(line);
	line = ft_strchr(line, ',');
	if (!line || !is_color_format(++line, ','))
		return (NO_COLOR);
	g = ft_atoi(line);
	line = ft_strchr(line, ',');
	if (!line || !is_color_format(++line, '\0'))
		return (NO_COLOR);
	b = ft_atoi(line);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (NO_COLOR);
	return (r << 16 | g << 8 | b);
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
