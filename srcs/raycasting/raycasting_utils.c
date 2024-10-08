/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/08 18:21:30 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//As long as the position of the character (=player), can be everywhere in the
//map, and within the map we work with cubes, we have to know where is the character
//but not in pixel, but in cubes unit.
//this function rounded_down the position of the player to give us his position
//in cubes unit

//this functions round the nb to the nearest down integer
//for this function there is 2 cases. If the number is > 0 or < 0
//if it's < 0, we have to be sure that it contains a decimal value < 0.0
//to avoid rounding an already integer number
double	rounded_down(double nb)
{
	if (nb < 0 && nb != (long)nb)
		return ((long)nb - 1);
	return ((long)nb);
}

/*#include <stdio.h>
int	main(void)
{
	double	nb_1 = -10.00;
	double	nb_2 = -1.10;
	double	nb_3 = -1.51;
	double	nb_4 = 0.000;
	double	nb_5 = 1.31;
	double	nb_6 = 1.51;
	double	nb_7 = 4.00;

	printf("nb_1 = %f\n", rounded_down(nb_1));
	printf("nb_2 = %f\n", rounded_down(nb_2));
	printf("nb_3 = %f\n", rounded_down(nb_3));
	printf("nb_4 = %f\n", rounded_down(nb_4));
	printf("nb_5 = %f\n", rounded_down(nb_5));
	printf("nb_6 = %f\n", rounded_down(nb_6));
	printf("nb_7 = %f\n", rounded_down(nb_7));
	return (0);
}*/

double	rounded_nearest_nb(double nb)
{
	double	nb_2;
	
	if (nb >= 0.0)
	{
		nb_2 = nb - rounded_down(nb);
		if (nb_2 == 0)
			return (nb);
		if (nb_2 > 0.50)
			return ((double)(rounded_down(nb) + 1));
		return ((double)(rounded_down(nb)));
	}
	else
	{
		nb_2 = nb - (long)nb;
		if (nb_2 == 0)
			return (nb);
		if (nb_2 > -0.50)
			return ((double)(rounded_down(nb) + 1));
		return ((double)(rounded_down(nb)));
	}
}

t_block	convert_pixel_to_block(t_block point)
{
	t_block	result;

	result.x = point.x / BLOCK_SIZE;
	result.y = point.y / BLOCK_SIZE;
	//printf("result.x = %f\nresult.y = %f\n", result.x, result.y);
	return (result);
}

//we need a function to know if the ray is facing up or down
//this function returns 1 if is going up, 0 if it's going down
//how to know if the angle is facing up ?
//We start from the abscissa axis and we go anticlockwise.
//We know that is facing up if the angle goes from 0° ≤ angle < 180 (% 360)
int	ray_facing_up(t_ray *ray)
{
	if (ray->angle >= 0 && ray->angle < 180)
		return (1);
	else
		return (0);
}

