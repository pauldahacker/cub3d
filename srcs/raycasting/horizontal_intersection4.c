/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:24:09 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/28 17:25:41 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//1st step: calculate the first intersection from the point with the horizontal line
//2nd step: checks if the point is on the map
//while the point is 0 || 'V'
//	calculate the next one
//	checking if it's on the map
//when the point is not fulfulling the condition, return the point

/*t_block	check_horizontal_first_pt(t_vars *vars, double ray_angle)
{
	t_block	first_intersected_point;
	
	first_intersected_point.reachable = 1;
	if (ray_facing_up(ray_angle) == 1)
		first_intersected_point.y = rounded_down(vars->game->player->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1.0;
	else
		first_intersected_point.y = rounded_down(vars->game->player->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	first_intersected_point.x = vars->game->player->pos_x + (vars->game->player->pos_y - first_intersected_point.y) / tan(ray_angle * (PI / 180.0));
	return (first_intersected_point);
}

double	horizontal_y_a(double ray_angle)
{
	if (ray_facing_up(ray_angle) == 1)
		return (-BLOCK_SIZE);
	return (BLOCK_SIZE);
}

double	horizontal_x_a(double ray_angle)
{
	double	x_a_iteration;
	
	if (ray_angle == 0.000000)
		ray_angle += 0.000001;
	x_a_iteration = ft_abs((BLOCK_SIZE / tan(ray_angle * PI / 180.0)));//maybe here you can rounded_down
	if (ray_facing_right(ray_angle) == 1)
		return (x_a_iteration);
	return (-x_a_iteration);
}

t_block	check_horizontal_next_pt(t_block horizontal_first_pt_px, double ray_angle)
{
	t_block	horizontal_next_pt_px;
	double	x_a;
	double	y_a;

	x_a = horizontal_x_a(ray_angle);
	y_a = horizontal_y_a(ray_angle);
	horizontal_first_pt_px.reachable = 1;
	horizontal_next_pt_px.x = rounded_down(horizontal_first_pt_px.x + x_a);
	horizontal_next_pt_px.y = rounded_down(horizontal_first_pt_px.y + y_a);
	// horizontal_next_pt_px.y = rounded_down(horizontal_first_pt_px.y) + y_a;
	// horizontal_next_pt_px.y = rounded_down(horizontal_first_pt_px.y) + rounded_down(y_a);
	return (horizontal_next_pt_px);
}

t_block	horizontal_point_crossing_wall(t_vars *vars, double ray_angle)
{
	t_block	horizontal_first_pt_px;
	t_block	horizontal_first_pt_block;
	t_block	horizontal_next_pt_px;
	t_block	horizontal_next_pt_block;
	char	**map;

	map = vars->game->map;
	horizontal_first_pt_px = check_horizontal_first_pt(vars, ray_angle);
	horizontal_first_pt_block = convert_pixel_to_block(horizontal_first_pt_px);
	if (check_coordinates_in_map(vars, horizontal_first_pt_block) == 0)
		return (horizontal_first_pt_px.reachable = 0, horizontal_first_pt_px);
	while (map[(int)horizontal_first_pt_block.y][(int)horizontal_first_pt_block.x] == 'V'
		|| map[(int)horizontal_first_pt_block.y][(int)horizontal_first_pt_block.x] == '0')
	{
		horizontal_next_pt_px = check_horizontal_next_pt(horizontal_first_pt_px, ray_angle);
		horizontal_next_pt_block = convert_pixel_to_block(horizontal_next_pt_px);
		if (check_coordinates_in_map(vars, horizontal_next_pt_block) == 0)
			return (horizontal_next_pt_px.reachable = 0, horizontal_next_pt_px);
		horizontal_first_pt_px = horizontal_next_pt_px;
		horizontal_first_pt_block = horizontal_next_pt_block;
	}
	return (horizontal_first_pt_px);
}*/