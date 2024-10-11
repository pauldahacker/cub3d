/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:25:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/11 11:43:12 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/player-casting-tutorial-7/

//We want to convert the position of our character (=player) that we have in 
//pixel into cubs unit.
//Given that the cubs unit are bigger than pixels, this returns an approximation

//This function gives us the coordinates of the character into block/cubs unit.
//tan receives an angle in radian but we work in degrees, so we add * (PI / 180)
//to convert it in radians
static t_block	horizontal_coordinate_first_block_point(t_player *player)
{
	t_block	a;

	a.reachable = 1;
	if (ray_facing_up(player->angle) == 1)
		a.y = rounded_down(player->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
	else
		a.y = rounded_down(player->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	
	check_horizontal_angle_value(player);
	a.x = player->pos_x + (player->pos_y - a.y) / tan(player->angle * (PI / 180));
	return (a);
}

static double	find_horizontal_x_a(t_player *player)
{
	return (rounded_down((double)BLOCK_SIZE / tan(player->angle * PI / 180)));
}

static double	find_horizontal_y_a(t_player *player)
{
	if (ray_facing_up(player->angle) == 1)
		return ((double)-BLOCK_SIZE);
	return ((double)BLOCK_SIZE);
}

t_block	horizontal_coordinate_next_block_point(t_player *player, t_block previous)
{
	t_block	next;
	double	x_a;
	double	y_a;

	x_a = find_horizontal_x_a(player);
	y_a = find_horizontal_y_a(player);
	// printf("\nin horizontal_coordinate_next_block_point\n");
	// printf("x_a = %f && y_a = %f\n", x_a, y_a);
	// printf("previous.x = %f && previous.y = %f\n", previous.x, previous.y);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	next.reachable = true;
	return (next);
}

//Ensuite on a besoin d'une fonction/condition qui nous dit que s'il y a un mur
//au point en (convertit en block) alors, on stop le process
//Sinon on continue jusqu'a le stopper

//This function find the first point, it means where the player is on the vars->game->map
//then checks if there is a wall or not. If there is no, we will go on 
//until finding one to return the point where the wall is

//une fois que l'on a next_in_x, on peut calculer la distance en pixel parcourue
t_block	horizontal_point_crossing_wall(t_vars *vars)
{
	t_block	current_in_block;
	t_block	current_in_px;
	t_block	next_in_block;
	t_block	next_in_px;

	current_in_px = horizontal_coordinate_first_block_point(vars->game->player);
	current_in_block = convert_pixel_to_block(current_in_px);
	current_in_block.x = rounded_nearest_nb(current_in_block.x);
	current_in_block.y = rounded_nearest_nb(current_in_block.y);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
	{
		current_in_px.reachable = false;
		return (current_in_px);
	}
	while (vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == '0'
			|| vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == 'V')
	{
		next_in_px = horizontal_coordinate_next_block_point(vars->game->player, current_in_px);
		next_in_block = convert_pixel_to_block(next_in_px);
		next_in_block.x = rounded_nearest_nb(next_in_block.x);
		next_in_block.y = rounded_nearest_nb(next_in_block.y);
		if (check_coordinates_in_map(vars, next_in_block) == 0)
		{
			current_in_px.reachable = false;
			return (current_in_px);
		}
		current_in_px = next_in_px;
		current_in_block = next_in_block;
	}
	return (current_in_px);
}

//we may need a function that checked if the point that we reached is out of bounds


void	print_result_point(t_vars *vars)
{
	t_block	horizontal_pt_px;
	t_block	horizontal_pt_block;

	horizontal_pt_px = horizontal_point_crossing_wall(vars);
	horizontal_pt_block = convert_pixel_to_block(horizontal_pt_px);
	if (horizontal_pt_px.reachable == 1)
	{
		printf("horizontal final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", horizontal_pt_px.y, horizontal_pt_px.x);
		printf("horizontal final point in \033[1;34mblock\033[0m y = %0.f && x = %0.f\n", horizontal_pt_block.y, horizontal_pt_block.x);
	}
	else
		printf("\033[1;29mhorizontal final point not reachable\033[0m\n");
	printf("\n");
	t_block	vertical_pt_px;
	t_block	vertical_pt_block;

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




	// printf("3 horizontal final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", current_in_px.y, current_in_px.x);
	// printf("horizontal final point in \033[1;34mblock\033[0m y = %0.f && x = %0.f\n", current_in_block.y, current_in_block.x);