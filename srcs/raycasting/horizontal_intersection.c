/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:25:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/12 21:40:27 by simon            ###   ########.fr       */
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
	check_horizontal_angle_value(player);
	if (ray_facing_up(player->angle) == 1)
		a.y = rounded_down(player->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
	else
		a.y = rounded_down(player->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	a.x = player->pos_x + (a.y - player->pos_y) / tan(player->angle * (PI / 180));
	// a.x = player->pos_x - (a.y - player->pos_y) / tan(player->angle * (PI / 180));
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
//REINITIALISE L'ANGLE UNE FOIS QUE TU AS TERMINE DE L'UTILISER
t_block	horizontal_point_crossing_wall(t_vars *vars)
{
	t_block	current_in_block;
	t_block	current_in_px;
	t_block	next_in_block;
	t_block	next_in_px;

	if (vars->game->player->angle > 180 && vars->game->player->angle < 360)
	 	vars->game->player->angle = 540 - vars->game->player->angle;
	current_in_px = horizontal_coordinate_first_block_point(vars->game->player);
	current_in_block = convert_pixel_to_block(current_in_px);
	current_in_block.x = rounded_nearest_nb(current_in_block.x);
	current_in_block.y = rounded_nearest_nb(current_in_block.y);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
	{
		current_in_px.reachable = false;
		vars->game->player->angle = vars->game->player->initial_angle;
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
			vars->game->player->angle = vars->game->player->initial_angle;
			return (current_in_px);
		}
		current_in_px = next_in_px;
		current_in_block = next_in_block;
	}
	return (current_in_px);
}

// printf("3 horizontal final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", current_in_px.y, current_in_px.x);
// printf("horizontal final point in \033[1;34mblock\033[0m y = %0.f && x = %0.f\n", current_in_block.y, current_in_block.x);