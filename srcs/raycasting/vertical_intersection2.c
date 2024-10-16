/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:24:33 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/16 19:26:23 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*t_block	vertical_coordinate_first_block_point(t_player *player)
{
	t_block	a;

	a.reachable = 1;
	check_vertical_angle_value(player);
	if (ray_facing_right(player->angle) == 1)
		a.x = rounded_down(player->pos_x / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	else
		a.x = rounded_down(player->pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;

	a.y = player->pos_y + (player->pos_x - a.x) * tan(player->angle * (PI / 180));
	return (a);
}

double	find_vertical_x_a(t_player *player)
{
	if (ray_facing_right(player->angle) == 1)
		return ((double)BLOCK_SIZE);
	return ((double)-BLOCK_SIZE);
}

//formula from the Pythagoras theorem to find the distance of the hypotenuse
//how to find the hypotenuse ? 
//We know the angle (player->ange) and the distance of one side of the triangle
//which is one cube (<=> BLOCK_SIZE unit)
double	find_vertical_y_a(t_player *player)
{
	return ((double)BLOCK_SIZE * tan(player->angle * (PI / 180)));
}

t_block	vertical_coordinate_next_block_point(t_player *player, t_block previous)
{
	t_block	next;
	double	x_a;
	double	y_a;

	x_a = find_vertical_x_a(player);
	y_a = find_vertical_y_a(player);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	next.reachable = true;
	return (next);
}

t_block	vertical_point_crossing_wall(t_vars *vars)
{
	t_block	current_in_block;
	t_block	current_in_px;
	t_block	next_in_block;
	t_block	next_in_px;

	current_in_px = vertical_coordinate_first_block_point(vars->game->player);
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
		next_in_px = vertical_coordinate_next_block_point(vars->game->player, current_in_px);
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