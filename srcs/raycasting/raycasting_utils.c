/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/04 11:06:07 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../headers/cub3d.h"
#include <stdio.h>

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

/*int	main(void)
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


