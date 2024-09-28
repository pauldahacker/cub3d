/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:57:22 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/28 13:11:19 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int main(int argc, char **argv)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	int		flag;

	flag = 0;
	j = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "failed to open the map\n", 23), 1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (write(1, "No 0 found in the map\n", 22), 0);
		j = 0;
		while (line[j])
		{
			if (line[j] == '0')
			{
				flag = 1;
				break ;
			}
			j++;
		}
		if (flag == 1)
			break ;
		i++;
	}
	printf("0 found in position map[%i][%i]\n", i, j);
	(void)argc;
	return (0);
}