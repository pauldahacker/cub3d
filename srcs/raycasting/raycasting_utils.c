/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/23 16:32:06 by simarcha         ###   ########.fr       */
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
	if (nb < 0.0 && nb != (long)nb)
		return ((long)nb - 1);
	return ((long)nb);
}

#include <stdio.h>

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

//rounded_nearest_nb
//you might not need the rounded_down function	
t_point	convert_pixel_to_block(t_point point)
{
	t_point	converted;

	converted.x = rounded_down(point.x / (double)BLOCK_SIZE);
	converted.y = rounded_down(point.y / (double)BLOCK_SIZE);
	return (converted);
}

//we need a function to know if the ray is facing up or down
//this function returns 1 if is going up, 0 if it's going down
//how to know if the angle is facing up ?
//We start from the abscissa axis and we go anticlockwise.
//We know that is facing up if the angle goes from 0° ≤ angle < 180 (% 360)
int	ray_facing_up(double angle)
{
	if (angle >= 0.0 && angle < 180.0)
		return (1);
	else
		return (0);
}

//we need thee function to know if the ray is facing right or left
//this function returns 1 if is going right, 0 if it's going left
//how to know if the angle is facing right ?
//We start from the abscissa axis and we go anticlockwise.
//Basically, we know that angle is facing right if the angle goes from 
//-90° ≤ angle ≤ 90 (everything % 360)
int	ray_facing_right(double angle)
{
	if ((angle >= -90.0 && angle < 90.0)
		|| (angle >= 270.0 && angle <= 360.0))
		return (1);
	else
		return (0);
}


// int	main(void)
// {
// 	double	nb_1 = -10.00;
// 	double	nb_2 = -1.10;
// 	double	nb_3 = -1.51;
// 	double	nb_4 = 0.000;
// 	double	nb_5 = 1.31;
// 	double	nb_6 = 1.51;
// 	double	nb_7 = 4.00;

// 	printf("nb_1 = %f\n", rounded_nearest_nb(nb_1));
// 	printf("nb_2 = %f\n", rounded_nearest_nb(nb_2));
// 	printf("nb_3 = %f\n", rounded_nearest_nb(nb_3));
// 	printf("nb_4 = %f\n", rounded_nearest_nb(nb_4));
// 	printf("nb_5 = %f\n", rounded_nearest_nb(nb_5));
// 	printf("nb_6 = %f\n", rounded_nearest_nb(nb_6));
// 	printf("nb_7 = %f\n", rounded_nearest_nb(nb_7));
// 	return (0);
// }

int	check_coordinates_in_map(t_vars *vars, t_point current)
{
	if (current.y < 0 || current.y > vars->game->n_rows - 1
		|| current.x < 0 || current.x > vars->game->n_cols - 1)
		return (0);
	return (1);
}
