/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:02:55 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/17 17:26:10 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//est_ce que le alpha_angle nous donne sa valeur en fonction de 0 degres ? ou 
//en fonction de middle angle ?
t_block	convert_pixel_to_block(t_block point);

t_block	find_coordinate_of_first_vertical_point(t_vars *vars)
{
	t_block	a;

	a.reachable = 1;
	if (ray_facing_right(vars->game->player->alpha_angle) == 1)//ray face right entre 0 et 180(exclus)
		a.x = rounded_down(vars->game->player->pos_x / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	else
		a.x = rounded_down(vars->game->player->pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;
	a.y = vars->game->player->pos_y + (vars->game->player->pos_x - a.x) * tan(vars->game->player->alpha_angle * (PI / 180));
	return (a);
}

double	finding_vertical_x_a(t_vars *vars)
{
	if (ray_facing_right(vars->game->player->alpha_angle) == 1)
		return (BLOCK_SIZE);
	return (-BLOCK_SIZE);
}

double	finding_vertical_y_a(t_vars *vars)
{
	return (BLOCK_SIZE * tan(vars->game->player->alpha_angle * (PI / 180)));
}

t_block	find_next_vertical_point(t_vars *vars, t_block current_point)
{
	t_block	next_in_px;
	double	x_a;
	double	y_a;
	
	x_a = finding_vertical_x_a(vars);
	y_a = finding_vertical_y_a(vars);
	next_in_px.x = current_point.x + x_a;
	next_in_px.y = current_point.y + y_a;
	return (next_in_px);
}

//starting from the character position, we want to cast a ray until we find a
//wall
t_block	vertical_point_crossing_wall(t_vars *vars)
{
	t_block	current_in_px;
	t_block	current_in_block;
	t_block	next_in_px;
	t_block	next_in_block;

	current_in_px = find_coordinate_of_first_vertical_point(vars);
	current_in_block = convert_pixel_to_block(current_in_px);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
		return (current_in_px.reachable = 0, current_in_px);
	while (vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == 'V'
		|| vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == '0')
	{
		next_in_px = find_next_vertical_point(vars, current_in_px);
		next_in_block = convert_pixel_to_block(next_in_px);
		if (check_coordinates_in_map(vars, next_in_block) == 0)
			return (current_in_px.reachable = 0, current_in_px);
		current_in_block = next_in_block;
		current_in_px = next_in_px;
	}
	return (next_in_px);
}
