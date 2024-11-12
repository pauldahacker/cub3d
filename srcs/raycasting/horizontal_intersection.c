/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:05:25 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/12 16:23:34 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_block	find_coordinate_of_first_horizontal_point(t_vars *vars)
{
	t_block	a;

	a.reachable = 1;
	if (ray_facing_up(vars->game->player->ray_angle) == 1)
		a.y = rounded_down(vars->game->player->pos_y / BLOCK_SIZE)
			* BLOCK_SIZE - 0.000001;
	else
		a.y = rounded_down(vars->game->player->pos_y / BLOCK_SIZE)
			* BLOCK_SIZE + BLOCK_SIZE;
	a.x = vars->game->player->pos_x + (vars->game->player->pos_y - a.y)
		/ tan(vars->game->player->ray_angle * (PI / 180.0));
	return (a);
}

static double	finding_horizontal_y_a(double ray_angle)
{
	if (ray_facing_up(ray_angle) == 1)
		return (-BLOCK_SIZE);
	return (BLOCK_SIZE);
}

static double	finding_horizontal_x_a(double ray_angle)
{
	double	x_a_iteration;

	x_a_iteration = ft_abs((double)BLOCK_SIZE / tan(ray_angle * (PI / 180.0)));
	if (ray_facing_right(ray_angle) == 1)
		return (x_a_iteration);
	return (-x_a_iteration);
}

static t_block	find_next_horizontal_point(t_block current_point,
	double ray_angle)
{
	t_block	next_in_px;
	double	x_a;
	double	y_a;

	x_a = finding_horizontal_x_a(ray_angle);
	y_a = finding_horizontal_y_a(ray_angle);
	next_in_px.x = current_point.x + x_a;
	next_in_px.y = current_point.y + y_a;
	next_in_px.reachable = true;
	return (next_in_px);
}

//we have a specific problem when we are looking the walls exactly in front of
//them, when they are configured in ascending diagonal
//01
//10
//because for each block, we look at the point (0,0) <=> the very first pixel
//What is happening if we are strictly looking in front of them ?
//We will see a blank line. Whereas we want to see both wall touched
//to avoid this, we check that we wall are not configured in ascending diagonal
//if there are not, then we can continue on our *_point_crossing_wall while loop
//otherwise we stop. The ray will stop and will draw a wall.
int	wall_not_in_ascending_diagonal(t_vars *vars, t_block current)
{
	char	**map;

	map = vars->game->map;
	if ((int)current.y > 0 && (int)current.x > 0 && 
		(map[(int)current.y][(int)current.x] == 'V' || map[(int)current.y][(int)current.x] == '0') &&
		map[(int)current.y - 1][(int)current.x] == '1' && 
		map[(int)current.y][(int)current.x - 1] == '1' &&
		(map[(int)current.y - 1][(int)current.x - 1] == 'V' || map[(int)current.y - 1][(int)current.x - 1] == '0')
		)
		return (0);
	return (1);
}

//starting from the character position, we want to cast a ray until we find a
//wall
t_block	horizontal_point_crossing_wall(t_vars *vars)
{
	t_block	current_in_px;
	t_block	current_in_block;
	t_block	next_in_px;
	t_block	next_in_block;
	char	**map;

	map = vars->game->map;
	current_in_px = find_coordinate_of_first_horizontal_point(vars);
	current_in_block = convert_pixel_to_block(current_in_px);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
		return (current_in_px.reachable = 0, current_in_px);
	while ((map[(int)current_in_block.y][(int)current_in_block.x] == 'V'
		|| map[(int)current_in_block.y][(int)current_in_block.x] == '0')
		&& wall_not_in_ascending_diagonal(vars, current_in_block) == 1)
		// && ((int)current_in_block.y > 0 && (int)current_in_block.x > 0
		// && (((map[(int)current_in_block.y - 1][(int)current_in_block.x] == 'V'
		// || map[(int)current_in_block.y][(int)current_in_block.x - 1] == 'V'))
		// || ((map[(int)current_in_block.y - 1][(int)current_in_block.x] == '0'
		// || map[(int)current_in_block.y][(int)current_in_block.x - 1] == '0')))))
	{
		next_in_px = find_next_horizontal_point(current_in_px,
			vars->game->player->ray_angle);
		next_in_block = convert_pixel_to_block(next_in_px);
		if (check_coordinates_in_map(vars, next_in_block) == 0)
			return (current_in_px.reachable = 0, current_in_px);
		current_in_block = next_in_block;
		current_in_px = next_in_px;
	}
	return (current_in_px);
}
