/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_angle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:01 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/14 19:03:23 by simarcha         ###   ########.fr       */
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

	rest = (int)rounded_nearest_nb(ray->angle) % 360;
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
int	check_coordinates_in_map(t_vars *vars, t_block current_point)
{
	// t_block	current_in_block;
	t_block	max_vision;

	// printf("check_coordinates_in_map\n");
	// printf("current_point.x = %f\n", current_point.x);
	// printf("current_point.y = %f\n", current_point.y);
	max_vision.x = (vars->game->n_rows - 1) * BLOCK_SIZE;
	max_vision.y = (vars->game->n_cols - 1) * BLOCK_SIZE;
	if (current_point.y < 0 || current_point.y > max_vision.y
		|| current_point.x < 0 || current_point.x > max_vision.x)
		return (0);
	return (1);
}