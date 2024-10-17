/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:02:23 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/17 17:24:42 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//We want to know the first point that crosses the first blockpoint
// => even if it's a wall or a empty cell

/*t_block	find_coordinate_first_intersection(t_vars *vars)
{
	t_block	a;
	
	if (ray_facing_up(vars->game->player->middle_angle) == 1)
		a.y = rounded_down(vars->game->player->pos_x / 64) * 64 - 1;
	else 
		a.y = rounded_down(vars->game->player->pos_x / 64) * 64 + 64;
	a.x = vars->game->player->pos_x + (vars->game->player->pos_y - a.y) / tan (vars->game->player->current_ray * PI / 180);
}



static t_block	horizontal_coordinate_first_block_point(t_player *player)
{
	t_block	a;

	a.reachable = 1;
	//check_horizontal_angle_value(player);
	if (ray_facing_up(player->angle) == 1)
		a.y = rounded_down(player->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
	else
		a.y = rounded_down(player->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
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
*/