/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_fd_into_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:11:39 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/28 15:10:34 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//we have our map which is a fd. We want to convert it into an array

//first, we should count how many characters there is in our map to know how
//much space we need for the memory allocation

void	print_map_array(char **map)
{
	int	x;
	int	y;

	x = 0;
	printf("in print_map_array\n");
	printf("print map[x] = %s\n", map[x]);
	while (map[x])
	{
		printf("4\n");
		y = 0;
		while (map[x][y] && map[x][y] != '\n')
		{
			printf("%c", map[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}

int	count_lines_in_map(int fd)
{
	int		nb_lines;
	char	*line;
	
	nb_lines = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		nb_lines += 1;
		free(line);
	}
	return (nb_lines);
}

char	**fd_into_array(int fd)
{
	char	**map_array;
	int		nb_lines;
	int		x;

	nb_lines = count_lines_in_map(fd);
	map_array = malloc(sizeof(char) * nb_lines);
	if (!map_array)
		return (NULL);
	x = 0;
	while (x < nb_lines)
	{
		map_array[x] = get_next_line(fd);
		printf("map_array[x] = %s\n", map_array[x]);
		if (!map_array[x])
			return (NULL);
		x++;
	}
	return (map_array);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	**map;
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "failed to open the map\n", 23), 1);
	printf("0\n");
	map = fd_into_array(fd);
	printf("1\n");
	print_map_array(map);
	printf("2\n");
	(void)argc;
	return (0);
}
