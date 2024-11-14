/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:49 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/12 18:55:14 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//As long as the position of the character (=player), can be everywhere in the
//map, and within the map we work with cubes, we have to know where is the
//character but not in pixel, but in cubes unit.
//this function floor the position of the player to give us his position
//in cubes unit

//the position on the map can be everywhere in pixel but will be always
//floor to the nearest int to suits with the map coordinates

//this functions round the nb to the nearest down integer
//for this function there is 2 cases. If the number is > 0 or < 0
//if it's < 0, we have to be sure that it contains a decimal value < 0.0
//to avoid rounding an already integer number
double	floor(double nb)
{
	if (nb < 0.0 && nb != (long)nb)
		return ((long)nb - 1);
	return ((long)nb);
}

double	round(double nb)
{
	double	nb_2;

	if (nb >= 0.0)
	{
		nb_2 = nb - floor(nb);
		if (nb_2 == 0)
			return (nb);
		if (nb_2 > 0.50)
			return ((double)(floor(nb) + 1));
		return ((double)(floor(nb)));
	}
	else
	{
		nb_2 = nb - (long)nb;
		if (nb_2 == 0)
			return (nb);
		if (nb_2 > -0.50)
			return ((double)(floor(nb) + 1));
		return ((double)(floor(nb)));
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

// 	printf("nb_1 = %f\n", round(nb_1));
// 	printf("nb_2 = %f\n", round(nb_2));
// 	printf("nb_3 = %f\n", round(nb_3));
// 	printf("nb_4 = %f\n", round(nb_4));
// 	printf("nb_5 = %f\n", round(nb_5));
// 	printf("nb_6 = %f\n", round(nb_6));
// 	printf("nb_7 = %f\n", round(nb_7));
// 	return (0);
// }
