/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_best_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:57:03 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/13 17:39:58 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//the goal of this file is to choose the shortest distance between the
//horizontal ray distance and the vertical ray distance
//for this will use the Pythagoras theorem because each ray are drawn in a 
//right triangle

double	ft_abs(double number)
{
	if (number >= 0.0)
		return (number);
	return (number * -1.0);
}

//This functions has to calculate the hypotenuse distance
//to find the adjacent distance, we will calculate the difference between both
//x points same for the opposite distance side, but with y coordinate
//then we use pyhagoras theorem
double	calculate_hypo_distance(t_vars *vars, t_block point)
{
	t_block	ray_end_pt;
	double	distance;

	ray_end_pt.x = ft_abs(vars->game->player->pos_x - point.x);
	ray_end_pt.y = ft_abs(vars->game->player->pos_y - point.y);
	distance = ray_end_pt.x * ray_end_pt.x + ray_end_pt.y * ray_end_pt.y;
	return (sqrt(distance));
}

//we calculate both distance between the horizontal intersection and the
//vertical intersection. Then we choose the minimal distance.
//we have to reset the angle to the initial one because in the funcions 
//*al_point_crossing_wall, we modify the value of the angle
//(for correct calculations)
t_block	calculate_best_distance(t_vars *vars, double angle)
{
	t_block	horizontal_pt_px;
	double	horizontal_distance;
	t_block	vertical_pt_px;
	double	vertical_distance;

	vars->game->player->angle = angle;
	horizontal_pt_px = horizontal_point_crossing_wall(vars);
	if (horizontal_pt_px.reachable == 1)
		horizontal_distance = calculate_hypo_distance(vars, horizontal_pt_px);
	else
		horizontal_distance = NAN;
	vars->game->player->angle = angle;
	vertical_pt_px = vertical_point_crossing_wall(vars);
	if (vertical_pt_px.reachable == 1)
		vertical_distance = calculate_hypo_distance(vars, vertical_pt_px);
	else
		vertical_distance = NAN;
	if (fmin(vertical_distance, horizontal_distance) == vertical_distance)
		return (vertical_pt_px);
	return (horizontal_pt_px);
}

// void	test_calculate_best_distance(t_vars *vars, double angle)
// {
// 	double	best_distance;

// 	printf("angle = %f\n", angle);
// 	best_distance = calculate_best_distance(vars, angle);
// 	printf("best_distance in px = %f\n", best_distance);
// 	printf("best_distance in block = %f\n", best_distance / BLOCK_SIZE);
// }