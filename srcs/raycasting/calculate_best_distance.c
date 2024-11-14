/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_best_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:57:03 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/13 19:00:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//the goal of this file is to choose the shortest distance between the
//horizontal ray distance and the vertical ray distance
//for this will use the Pythagoras theorem because each ray are drawn in a 
//right triangle

t_block	convert_pixel_to_block(t_block point)
{
	t_block	converted;

	converted.x = point.x / BLOCK_SIZE;
	converted.y = point.y / BLOCK_SIZE;
	return (converted);
}

//This functions has to calculate the hypotenuse distance
//to find the adjacent distance, we will calculate the difference between both
//x points same for the opposite distance side, but with y coordinate
//then we use pyhagoras theorem
//to remove the fishbowl effect, we multiply the result with cos(beta)
//see: https://permadi.com/1996/05/ray-casting-tutorial-8/
static double	calculate_hypo_distance(t_vars *vars, t_block point)
{
	t_block	ray_end_pt;
	double	distance;
	double	beta;

	if (point.reachable == false)
		return (NAN);
	ray_end_pt.x = fabs(vars->game->player->pos_x - point.x);
	ray_end_pt.y = fabs(vars->game->player->pos_y - point.y);
	distance = ray_end_pt.x * ray_end_pt.x + ray_end_pt.y * ray_end_pt.y;
	beta = vars->game->player->middle_fov_angle - vars->game->player->ray_angle;
	return (sqrt(distance) * cos(beta * (PI / 180.0)));
}

//we calculate both distance between the horizontal intersection and the
//vertical intersection. Then we choose the minimal distance.
//we have to reset the angle to the initial one because in the funcions 
//*_point_crossing_wall, we modify the value of the angle
//(for correct calculations)
double	calculate_best_distance(t_vars *vars)
{
	t_block	horizontal_pt_px;
	double	horizontal_distance;
	t_block	vertical_pt_px;
	double	vertical_distance;

	horizontal_pt_px = horizontal_point_crossing_wall(vars);
	horizontal_distance = calculate_hypo_distance(vars, horizontal_pt_px);
	vertical_pt_px = vertical_point_crossing_wall(vars);
	vertical_distance = calculate_hypo_distance(vars, vertical_pt_px);
	if (fmin(vertical_distance, horizontal_distance) == vertical_distance)
	{
		vars->game->player->horizontal_distance_chosen = false;
		vars->game->player->point_hit = vertical_pt_px;
		return (vertical_distance);
	}
	else
	{
		vars->game->player->horizontal_distance_chosen = true;
		vars->game->player->point_hit = horizontal_pt_px;
		return (horizontal_distance);
	}
}

//returns the vertical or horizontal intersection with the smallest distance
t_block	return_intersection(t_vars *vars, double angle)
{
	t_block	horizontal_pt_px;
	double	horizontal_distance;
	t_block	vertical_pt_px;
	double	vertical_distance;
	double	ray_angle_tmp;

	ray_angle_tmp = vars->game->player->ray_angle;
	vars->game->player->ray_angle = angle;
	horizontal_pt_px = horizontal_point_crossing_wall(vars);
	if (horizontal_pt_px.reachable == 1)
		horizontal_distance = calculate_hypo_distance(vars, horizontal_pt_px);
	else
		horizontal_distance = NAN;
	vertical_pt_px = vertical_point_crossing_wall(vars);
	if (vertical_pt_px.reachable == 1)
		vertical_distance = calculate_hypo_distance(vars, vertical_pt_px);
	else
		vertical_distance = NAN;
	vars->game->player->ray_angle = ray_angle_tmp;
	if (fmin(vertical_distance, horizontal_distance) == vertical_distance)
		return (vertical_pt_px);
	return (horizontal_pt_px);
}
