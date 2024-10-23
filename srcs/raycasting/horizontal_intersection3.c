/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:05:25 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/23 16:32:06 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	find_coordinate_of_first_horizontal_point(t_vars *vars, double ray_angle)
{
	t_point	a;

	a.reachable = 1;
	if (ray_facing_up(ray_angle) == 1)
		a.y = rounded_down(vars->game->player->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
	else
		a.y = rounded_down(vars->game->player->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	a.x = vars->game->player->pos_x + (vars->game->player->pos_y - a.y) / tan(ray_angle * (PI / 180.0));
	printf("find_coordinate_of_first_horizontal_point first_point a.x = %f && a.y = %f\n", a.x, a.y);
	return (a);
}

double	finding_horizontal_y_a(double ray_angle)
{
	if (ray_facing_up(ray_angle) == 1)
		return (-BLOCK_SIZE);
	return (BLOCK_SIZE);
}

double	finding_horizontal_x_a(double ray_angle)
{
	double	x_a_iteration;

	x_a_iteration = ft_abs((double)BLOCK_SIZE / tan(ray_angle * (PI / 180.0)));
	if (ray_facing_right(ray_angle) == 1)
		return (x_a_iteration);
	return (-x_a_iteration);
	// return ((double)BLOCK_SIZE / tan(ray_angle * (PI / 180.0)));
}

t_point	find_next_horizontal_point(t_point current_point, double ray_angle)
{
	t_point	next_in_px;
	double	x_a;
	double	y_a;

	x_a = finding_horizontal_x_a(ray_angle);
	y_a = finding_horizontal_y_a(ray_angle);
	next_in_px.x = current_point.x + x_a;
	next_in_px.y = current_point.y + y_a;
	next_in_px.reachable = true;
	printf("next_point.x = %f && next_point.y = %f\n", next_in_px.x, next_in_px.y);
	return (next_in_px);
}

//starting from the character position, we want to cast a ray until we find a
//wall
t_point	horizontal_point_crossing_wall(t_vars *vars, double ray_angle)
{
	t_point	current_in_px;
	t_point	current_in_block;
	t_point	next_in_px;
	t_point	next_in_block;

	current_in_px = find_coordinate_of_first_horizontal_point(vars, ray_angle);
	current_in_block = convert_pixel_to_block(current_in_px);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
		return (current_in_px.reachable = 0, current_in_px);
	while (vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == 'V'
		|| vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == '0')
	{
		next_in_px = find_next_horizontal_point(current_in_px, ray_angle);
		next_in_block = convert_pixel_to_block(next_in_px);
		if (check_coordinates_in_map(vars, next_in_block) == 0)
			return (current_in_px.reachable = 0, current_in_px);
		current_in_block = next_in_block;
		current_in_px = next_in_px;
	}
	return (current_in_px);
}
