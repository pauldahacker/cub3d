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

int	is_space(int c)
{
	return (c == '\t' || c == '\n' || c == ' '
		|| c == '\f' || c == '\r' || c == '\v');
}

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
int	is_color_format(char *line, char next_separator)
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
