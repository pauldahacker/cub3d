/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:02:55 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/14 20:18:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_block	find_coordinate_of_first_vertical_point(t_vars *vars)
{
	t_block	a;

	a.reachable = 1;
	if (ray_facing_right(vars->game->player->ray_angle) == 1)
		a.x = floor(vars->game->player->pos_x / BLOCK_SIZE)
			* BLOCK_SIZE + BLOCK_SIZE;
	else
		a.x = floor(vars->game->player->pos_x / BLOCK_SIZE)
			* BLOCK_SIZE - 0.000001;
	a.y = vars->game->player->pos_y + (vars->game->player->pos_x - a.x)
		* tan(vars->game->player->ray_angle * (PI / 180.0));
	return (a);
}

static double	finding_vertical_x_a(double ray_angle)
{
	if (ray_facing_right(ray_angle) == 1)
		return (BLOCK_SIZE);
	return (-BLOCK_SIZE);
}

static double	finding_vertical_y_a(double ray_angle)
{
	double	y_a_iteration;

	y_a_iteration = fabs((double)BLOCK_SIZE * tan(ray_angle * (PI / 180.0)));
	if (ray_facing_up(ray_angle) == 1)
		return (-y_a_iteration);
	return (y_a_iteration);
}

static t_block	find_next_vertical_point(t_block current_point,
	double ray_angle)
{
	t_block	next_in_px;
	double	x_a;
	double	y_a;

	x_a = finding_vertical_x_a(ray_angle);
	y_a = finding_vertical_y_a(ray_angle);
	next_in_px.x = current_point.x + x_a;
	next_in_px.y = current_point.y + y_a;
	next_in_px.reachable = true;
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
	char	**map;

	map = vars->game->map;
	current_in_px = find_coordinate_of_first_vertical_point(vars);
	current_in_block = convert_pixel_to_block(current_in_px);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
		return (current_in_px.reachable = 0, current_in_px);
	while (map[(int)current_in_block.y][(int)current_in_block.x] == 'V'
		&& wall_not_in_diagonal(vars, current_in_block) == 1)
	{
		next_in_px = find_next_vertical_point(current_in_px,
				vars->game->player->ray_angle);
		next_in_block = convert_pixel_to_block(next_in_px);
		if (check_coordinates_in_map(vars, next_in_block) == 0)
			return (current_in_px.reachable = 0, current_in_px);
		current_in_block = next_in_block;
		current_in_px = next_in_px;
	}
	return (current_in_px);
}
