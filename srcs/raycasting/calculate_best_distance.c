/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_best_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:57:03 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/12 20:52:58 by simon            ###   ########.fr       */
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

	// printf("player->pos_x in px = %f\n", vars->game->player->pos_x);
	// printf("player->pos_y in px = %f\n", vars->game->player->pos_y);
	// printf("player->pos_x in block = %f\n", vars->game->player->pos_x / BLOCK_SIZE);
	// printf("player->pos_y in block = %f\n", vars->game->player->pos_y / BLOCK_SIZE);
	// printf("soustraction.x = %f\n", vars->game->player->pos_x - point.x);
	// printf("soustraction.y = %f\n", vars->game->player->pos_y - point.y);
	ray_final_point.x = ft_abs(vars->game->player->pos_x - point.x);
	ray_final_point.y = ft_abs(vars->game->player->pos_y - point.y);
	// printf("adjacent_point.x = %f\n", adjacent_point.x);
	// printf("adjacent_point.y = %f\n", adjacent_point.y);
	distance = ray_final_point.x * ray_final_point.x + ray_final_point.y * ray_final_point.y;
	return (sqrt(distance));
}

void	test_calculate_adjacent_side(t_vars *vars)
{
	t_block	horizontal_pt_px;
	t_block	horizontal_pt_block;
	int		angle;

	angle = 205;
	vars->game->player->angle = angle;
	horizontal_pt_px = horizontal_point_crossing_wall(vars);
	horizontal_pt_block = convert_pixel_to_block(horizontal_pt_px);
	if (horizontal_pt_px.reachable == 1)
	{
		printf("horizontal final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", horizontal_pt_px.y, horizontal_pt_px.x);
		printf("horizontal final point in \033[1;34mblock\033[0m y = %0.f && x = %0.f\n", horizontal_pt_block.y, horizontal_pt_block.x);
	}
	else
		printf("\033[1;29mhorizontal final point not reachable\033[0m\n");

	double	distance;
	distance = calculate_adjacent_distance(vars, horizontal_pt_px);
	printf("adjacent_distance in px = %f\n", distance);
	printf("adjacent_distance in block = %f\n", distance / BLOCK_SIZE);
	printf("\n");
	printf("\n");
	t_block	vertical_pt_px;
	t_block	vertical_pt_block;

	vars->game->player->angle = angle;
	vertical_pt_px = vertical_point_crossing_wall(vars);
	vertical_pt_block = convert_pixel_to_block(vertical_pt_px);
	if (vertical_pt_px.reachable == 1)
	{
		printf("vertical final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", vertical_pt_px.y, vertical_pt_px.x);
		printf("vertical final point in \033[1;34mblock\033[0m y = %0.f && x = %0.f\n", vertical_pt_block.y, vertical_pt_block.x);
	}
	else
		printf("\033[1;29mvertical final point not reachable\033[0m\n");
}













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

