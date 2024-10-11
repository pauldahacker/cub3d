/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_best_distance.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:57:03 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/11 19:34:13 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//the goal of this file is to choose the shortest distance between the
//horizontal ray distance and the vertical ray distance
//for this will use the Pythagoras theorem because each ray are drawn in a 
//right triangle

//you need a function to calculate the hypotenuse of the right triangle 
double	pythagoras(double adjacent_side, double opposite_side)
{
	double	hypotenuse_squared;

	hypotenuse_squared = adjacent_side * adjacent_side + opposite_side * opposite_side;
	return (sqrt(hypotenuse_squared));
}

double	ft_abs(double number)
{
	if (number >= 0.0)
		return (number);
	return (number * -1.0);
}

//we want to find where is the final point of our adjacent_side
//we know the initial point, which is the character coordinates (start)
//the final adjacent_side point is where the final ray point finishs
t_block	calculate_adjacent_distance(t_vars *vars, t_block point)
{
	t_block	adjacent_side;

	adjacent_side.x = ft_abs(vars->game->player->pos_x - point.x);
	adjacent_side.y = ft_abs(vars->game->player->pos_y - point.y);
	return (adjacent_side);
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

	t_block	adjacent_side;
	adjacent_side = calculate_adjacent_distance();
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

