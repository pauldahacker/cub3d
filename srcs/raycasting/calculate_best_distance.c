/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_best_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:57:03 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/12 21:41:22 by simon            ###   ########.fr       */
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

//to find the adjacent distance, we will calculate the difference between both x points
//same for the opposite distance side, but with y coordinate
//then we use pyhagoras theorem
double	calculate_hypotenuse_distance(t_vars *vars, t_block point)
{
	t_block	ray_final_point;
	double	distance;

	ray_final_point.x = ft_abs(vars->game->player->pos_x - point.x);
	ray_final_point.y = ft_abs(vars->game->player->pos_y - point.y);
	distance = ray_final_point.x * ray_final_point.x + ray_final_point.y * ray_final_point.y;
	printf("distance before sqrt: %f\n", distance);
	return (sqrt(distance));
}

double	calculate_best_distance(t_vars *vars, double angle)
{
	t_block	horizontal_pt_px;
	double	horizontal_distance;
	t_block	vertical_pt_px;
	double	vertical_distance;
	
	vars->game->player->angle = angle;
	horizontal_pt_px = horizontal_point_crossing_wall(vars);
	if (horizontal_pt_px.reachable == 1)
		horizontal_distance = calculate_hypotenuse_distance(vars, horizontal_pt_px);
	else
		horizontal_distance = NAN;
	// printf("horizontal distance in px = %f\n", horizontal_distance);
	// printf("horizontal distance in block = %f\n", horizontal_distance / BLOCK_SIZE);
	
	vars->game->player->angle = angle;
	vertical_pt_px = vertical_point_crossing_wall(vars);
	if (vertical_pt_px.reachable == 1)
		vertical_distance = calculate_hypotenuse_distance(vars, vertical_pt_px);
	else
		vertical_distance = NAN;
	// printf("vertical distance in px = %f\n", vertical_distance);
	// printf("vertical distance in block = %f\n", vertical_distance / BLOCK_SIZE);
	return (fmin(vertical_distance, horizontal_distance));
}

// void	test_calculate_best_distance(t_vars *vars, double angle)
// {
// 	double	best_distance;

// 	printf("angle = %f\n", angle);
// 	best_distance = calculate_best_distance(vars, angle);
// 	printf("best_distance in px = %f\n", best_distance);
// 	printf("best_distance in block = %f\n", best_distance / BLOCK_SIZE);
// }













// t_block	calculate_best_distance(t_vars *vars)
// {
// 	t_block	horizontal_pt_px;
// 	t_block	horizontal_pt_block;
// 	t_block	vertical_pt_px;
// 	t_block	vertical_pt_block;

// 	horizontal_pt_px = horizontal_point_crossing_wall(vars);
// 	horizontal_pt_block = convert_pixel_to_block(horizontal_pt_px);
// 	vertical_pt_px = vertical_point_crossing_wall(vars);
// 	vertical_pt_block = convert_pixel_to_block(vertical_pt_px);
// 	// if (horizontal_pt_px.reachable == 0)
// 	// {
// 	// 	pythagoras
// 	// }
// 	// else if (vertical_pt_px.reachable == 0)
// 	// {
		
// 	// }
// 	return ();
// }

