/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_fd_into_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:39 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/08 15:19:53 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Our game map is a file. We want to convert the map of this file into an array.
//First, we should count how many lines there is in our map to know how
//much space we need for the memory allocation
//Then in these lines we will insert the content

//I have to open and close the fd to reset the buffer reader head
//In the function get_next_line, we use the function read (2)
//in the read function, each time we use it, 
//the buffer's reader head is moving to read each character of the fd.
//to reset it to the beginning of the file, I close the fd
static int	count_lines_in_map(char *argv_1)
{
	int		nb_lines;
	char	*line;
	int		fd;

	fd = open(argv_1, O_RDONLY);
	if (fd == -1)
		return (write(2, "failed to open the map\n", 23), 1);
	nb_lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		nb_lines += 1;
		free(line);
	}
	close(fd);
	return (nb_lines);
}

//if one of the malloc fails inside of the array, we have to free everything
//in a proper way
void	free_array(char **array)
{
	int	x;

	x = 0;
	while (array[x])
	{
		free(array[x]);
		array[x] = NULL;
		x++;
	}
	free(array);
	array = NULL;
}

char	**fd_into_array(char *argv_1)
{
	char	**map_array;
	int		x;
	int		fd;
	int		nb_lines;

	nb_lines = count_lines_in_map(argv_1);
	fd = open(argv_1, O_RDONLY);
	if (fd == -1)
		return (write(2, "failed to reopen the map\n", 25), NULL);
	map_array = malloc(sizeof(*map_array) * (nb_lines + 1));
	if (!map_array)
		return (NULL);
	x = 0;
	while (x < nb_lines)
	{
		map_array[x] = get_next_line(fd);
		if (!map_array[x])
			return (free_array(map_array), NULL);
		x++;
	}
	map_array[x] = (void *) '\0';
	return (map_array);
}

void	print_map_array(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			write(1, &map[x][y], 1);
			y++;
		}
		x++;
	}
}

/*int	main(int argc, char **argv)
{
	char	**map;

	map = fd_into_array(argv[1]);
	print_map_array(map);
	free_array(map);
	(void)argc;
	return (0);
}*/
