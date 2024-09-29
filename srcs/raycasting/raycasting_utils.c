/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/25 17:17:26 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//As long as the position of the character (=player), can be everywhere in the
//map, and within the map we work with cubes, we have to know where is the character
//but not in pixel, but in cubes unit.
//this function rounded_down the position of the player to give us his position
//in cubes unit
double	rounded_down(double position)
{
	if (position >= 0)
		position = (long)position;
	else
		position = (long)position - 1;
	return ((double)position);
}

// #include <stdio.h>
// int	main(void)
// {
// 	double	position = -1.99;
// 	printf("position = %f\n", rounded_down(position));
// 	return (0);
// }