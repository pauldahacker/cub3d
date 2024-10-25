/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_best_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:57:03 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/25 13:07:12 by simarcha         ###   ########.fr       */
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
//to remove the fishbowl effect, we multiply the result with cos(beta)
//see: https://permadi.com/1996/05/ray-casting-tutorial-8/
double	calculate_hypo_distance(t_vars *vars, t_block point, double ray_angle)
{
	t_block	ray_end_pt;
	double	distance;
	double	beta;

	ray_end_pt.x = ft_abs(vars->game->player->pos_x - point.x);
	ray_end_pt.y = ft_abs(vars->game->player->pos_y - point.y);
	distance = ray_end_pt.x * ray_end_pt.x + ray_end_pt.y * ray_end_pt.y;
	beta = vars->game->player->angle - ray_angle;
	return (sqrt(distance) * cos(beta * (PI / 180.0)));
}

//we calculate both distance between the horizontal intersection and the
//vertical intersection. Then we choose the minimal distance.
//we have to reset the angle to the initial one because in the funcions 
//*_point_crossing_wall, we modify the value of the angle
//(for correct calculations)
double	calculate_best_distance(t_vars *vars, double ray_angle)
{
	t_block	horizontal_pt_px;
	double	horizontal_distance;
	t_block	vertical_pt_px;
	double	vertical_distance;

	t_block	tmp;//to remove
	horizontal_pt_px = horizontal_point_crossing_wall(vars, ray_angle);
	tmp = convert_pixel_to_block(horizontal_pt_px);//to remove
	printf("horizontal_pt_in_block.x = %f && horizontal_pt_in_block.y = %f\n", tmp.x, tmp.y);//to remove
	if (horizontal_pt_px.reachable == 1)
	{
		horizontal_distance = calculate_hypo_distance(vars, horizontal_pt_px, ray_angle);
		printf("horizontal_distance = %f\n", horizontal_distance);
	}
	else
		horizontal_distance = NAN;
	vertical_pt_px = vertical_point_crossing_wall(vars, ray_angle);
	tmp = convert_pixel_to_block(horizontal_pt_px);//to remove
	printf("vertical_pt_in_block.x = %f && vertical_pt_in_block.y = %f\n", tmp.x, tmp.y);//to remove
	if (vertical_pt_px.reachable == 1)
	{
		vertical_distance = calculate_hypo_distance(vars, vertical_pt_px, ray_angle);
		printf("vertical distance = %f\n", vertical_distance);
	}
	else
		vertical_distance = NAN;
	// return (fmin(vertical_distance, horizontal_distance));
	if (fmin(vertical_distance, horizontal_distance) == vertical_distance)
		return (printf("vertical distance chosen\n"), vertical_distance);
	return (printf("horizontal distance used\n"), horizontal_distance);
	printf("\n");
}

//returns the vertical or horizontal intersection with the smallest distance
t_block	return_intersection(t_vars *vars, double angle)
{
	t_block	horizontal_pt_px;
	double	horizontal_distance;
	t_block	vertical_pt_px;
	double	vertical_distance;

	horizontal_pt_px = horizontal_point_crossing_wall(vars, angle);
	if (horizontal_pt_px.reachable == 1)
		horizontal_distance = calculate_hypo_distance(vars, horizontal_pt_px, angle);
	else
		horizontal_distance = NAN;
	vertical_pt_px = vertical_point_crossing_wall(vars, angle);
	if (vertical_pt_px.reachable == 1)
		vertical_distance = calculate_hypo_distance(vars, vertical_pt_px, angle);
	else
		vertical_distance = NAN;
	if (fmin(vertical_distance, horizontal_distance) == vertical_distance)
		return (vertical_pt_px);
	return (horizontal_pt_px);
}
