#include "parsing.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <pde-masc@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:29:36 by pde-masc          #+#    #+#             */
/*   Updated: 2024/02/08 22:00:05 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_readable(char *file)
{
	int	fd;
	int	flag;

	fd = open(file, O_RDONLY);
	if (read(fd, 0, 0) < 0)
		flag = 0;
	else
		flag = 1;
	close(fd);
	return (flag);
}

int	is_format(char *str, char *ext)
{
	int	len;
	int	formatlen;
	int	i;

	len = ft_strlen(str);
	formatlen = ft_strlen(ext);
	i = 1;
	while (str[len - i] && ext[formatlen - i])
	{
		if (str[len - i] != ext[formatlen - i])
			return (0);
		i++;
	}
	return (1);
}

void	handle_error(char *str)
{
    if (str)
	    write(STDERR_FILENO, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	check_args(int argc, char **argv)
{
	if (argc != 2)
		handle_error("Error\nToo few or too many arguments!\n");
	else if (!is_readable(argv[1]))
		handle_error("Error\nRead error!\n");
	else if (!is_format(argv[1], MAP_EXTENSION))
		handle_error("Error\nMap has wrong extension!\n");
}
