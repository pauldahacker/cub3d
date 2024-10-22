/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_best_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:57:03 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/22 17:04:02 by simarcha         ###   ########.fr       */
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
	distance = sqrt(ray_end_pt.x * ray_end_pt.x + ray_end_pt.y * ray_end_pt.y);
	beta = vars->game->player->middle_angle - ray_angle;
	return (distance * cos(beta * (PI / 180.0)));
}

//we calculate both distance between the horizontal intersection and the
//vertical intersection. Then we choose the minimal distance.
double	calculate_best_distance(t_vars *vars, double ray_angle)
{
	t_block	horizontal_pt_px;
	double	horizontal_distance;
	t_block	vertical_pt_px;
	double	vertical_distance;
	
	horizontal_pt_px = horizontal_point_crossing_wall(vars, ray_angle);
	printf("new_point\n");//////
	t_block tmp;
	printf("horizontal_pt_px.x = %f && horizontal_pt_px.y = %f\n", horizontal_pt_px.x, horizontal_pt_px.y);
	tmp = horizontal_pt_px;
	horizontal_pt_px = convert_pixel_to_block(horizontal_pt_px);
	printf("horizontal_pt_block.x = %f && horizontal_pt_block.y = %f\n", horizontal_pt_px.x, horizontal_pt_px.y);
	horizontal_pt_px = tmp;//TO REMOVE
	
	if (horizontal_pt_px.reachable == 1)
		horizontal_distance = calculate_hypo_distance(vars, horizontal_pt_px, ray_angle);
	else
		horizontal_distance = NAN;

	printf("horizontal_distance = %f\n", horizontal_distance);//TO REMOVE

	vertical_pt_px = vertical_point_crossing_wall(vars, ray_angle);
	
	printf("vertical_pt_px.x = %f && vertical_pt_px.y = %f\n", vertical_pt_px.x, vertical_pt_px.y);//////
	tmp = vertical_pt_px;
	vertical_pt_px = convert_pixel_to_block(vertical_pt_px);
	printf("vertical_pt_block.x = %f && vertical_pt_block.y = %f\n", vertical_pt_px.x, vertical_pt_px.y);
	vertical_pt_px = tmp;//TO REMOVE

	if (vertical_pt_px.reachable == 1)
		vertical_distance = calculate_hypo_distance(vars, vertical_pt_px, ray_angle);
	else
		vertical_distance = NAN;
//	return (fmin(vertical_distance, horizontal_distance));

	
	if (fmin(vertical_distance, horizontal_distance) == vertical_distance)
	{
		// return (printf("\033[1;31mvertical distance\033[0m chosen\n\n"), vertical_distance);
		return (printf("vertical distance chosen\n\n"), vertical_distance);
	}
	// return (printf("\033[1;34mhorizontal_distance\033[0m chosen\n\n"), horizontal_distance);
	return (printf("HORIZONTAL_distance\n\n"), horizontal_distance);
}
