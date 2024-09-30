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
Returns str with ending whitespaces removed.
e.g. "Hello I am Paul  \n \t " --> "Hello I am Paul"
*/
char	*trim_end_spaces(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	while (is_space(str[--i]))
		str[i] = '\0';
	return (str);
}

/*
Takes line, which should be formatted like this: "r,g,b"
Where r,g,b represent numbers in range [0,255].
Returns color in decimal form, or exits with error if not correctly formatted.

!!! check atoi for invalid numbers (0 or error)
*/
int	return_rgb(char *line)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	g = ft_atoi(line);
	line = ft_strchr(line, ',') + 1;
	b = ft_atoi(line);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		handle_error("Error\nIncorrect color format\n");
	return (r << 16 | g << 8 | b);
}
