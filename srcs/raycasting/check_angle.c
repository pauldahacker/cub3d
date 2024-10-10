/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_angle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:01 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/10 12:33:17 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//the angle gives us a problem if we divide by 0 or if we multiply by ±∞
//in the horizontal_intersection.c file we have to check that the ray->angle is
//not 180 and is not 0. Otherwise, tan(ray->angle * PI / 180) = 0
//and the division will be impossible. This will lead to a segfault.
//This function checks that ray->angle is not the one that will gives segfault
void	check_horizontal_angle_value(t_player *ray)
{
	int	rest;

	rest = (int)rounded_nearest_nb(ray->angle) % 180;
	if (rest == 180)
		ray->angle = 181;
	else if (rest == 0)
		ray->angle = 1;
}

//in the vertical_intersection.c file we have to check that the ray->angle is
//not 90 and is not 270. Otherwise, tan(ray->angle * PI / 180) = ±∞
void	check_vertical_angle_value(t_player *ray)
{
	int	rest;

	rest = (int)rounded_nearest_nb(ray->angle) % 360;
	if (rest == 90)
		ray->angle = 91;
	else if (rest == 270)
		ray->angle = 271;
}

//we need a function need to checks if the point that we newly found after the
//iteration is in the map
//it's not in the map if:
//x || y < 0
//x > x_max || y > y_max
//if map[x][y] is different from 0 || 1

int	check_coordinates_in_map(t_vars *vars, t_block current)
{
	if (current.y < 0 || current.y > vars->game->n_rows
		|| current.x < 0 || current.x > vars->game->n_cols)
		return (0);
	return (1);
}