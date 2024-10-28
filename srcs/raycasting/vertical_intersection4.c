/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:43:31 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/28 20:11:39 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//est-ce que vars->game->player->pos_x est un entier ? 
//Non => est-ce que first_intersected_point.y doit etre rounded_down ?
/*t_block	check_vertical_first_pt(t_vars *vars, double ray_angle)
{
	t_block	first_intersected_point;
	
	first_intersected_point.reachable = 1;
	if (ray_facing_right(ray_angle) == 1)
		first_intersected_point.x = rounded_down(vars->game->player->pos_x / BLOCK_SIZE)
		* BLOCK_SIZE + BLOCK_SIZE;
	else
		first_intersected_point.x = rounded_down(vars->game->player->pos_x / BLOCK_SIZE)
		* BLOCK_SIZE - 1.0;
	first_intersected_point.y = vars->game->player->pos_y + (vars->game->player->pos_x - first_intersected_point.x)
	* tan(ray_angle * PI / 180.0);
	return (first_intersected_point);
}

double	vertical_x_a(double ray_angle)
{
	if (ray_facing_right(ray_angle) == 1)
		return (BLOCK_SIZE);
	return (-BLOCK_SIZE);
}

double	vertical_y_a(double ray_angle)
{
	double	y_a_iteration;
	
	if (ray_angle == 90.000000)
		ray_angle += 0.000001;
	y_a_iteration = ft_abs(rounded_down(BLOCK_SIZE * tan(ray_angle * PI / 180.0)));//maybe here you can rounded_down
	if (ray_facing_up(ray_angle) == 1)
		return (-y_a_iteration);
	return (y_a_iteration);
}

t_block	check_vertical_next_pt(t_block vertical_first_pt_px, double ray_angle)
{
	t_block	vertical_next_pt_px;
	double	x_a;
	double	y_a;

	x_a = vertical_x_a(ray_angle);
	y_a = vertical_y_a(ray_angle);
	vertical_first_pt_px.reachable = 1;
	vertical_next_pt_px.x = rounded_down(vertical_first_pt_px.x) + x_a;
	vertical_next_pt_px.y = rounded_down(vertical_first_pt_px.y) + y_a;
	// vertical_next_pt_px.y = rounded_down(vertical_first_pt_px.y) + y_a;
	// vertical_next_pt_px.y = rounded_down(vertical_first_pt_px.y) + rounded_down(y_a);
	return (vertical_next_pt_px);
}

t_block	vertical_point_crossing_wall(t_vars *vars, double ray_angle)
{
	t_block	vertical_first_pt_px;
	t_block	vertical_first_pt_block;
	t_block	vertical_next_pt_px;
	t_block	vertical_next_pt_block;
	char	**map;

	map = vars->game->map;
	vertical_first_pt_px = check_vertical_first_pt(vars, ray_angle);
	vertical_first_pt_block = convert_pixel_to_block(vertical_first_pt_px);
	if (check_coordinates_in_map(vars, vertical_first_pt_block) == 0)
		return (vertical_first_pt_px.reachable = 0, vertical_first_pt_px);
	while (map[(int)vertical_first_pt_block.y][(int)vertical_first_pt_block.x] == 'V'
		|| map[(int)vertical_first_pt_block.y][(int)vertical_first_pt_block.x] == '0')
	{
		vertical_next_pt_px = check_vertical_next_pt(vertical_first_pt_px, ray_angle);
		vertical_next_pt_block = convert_pixel_to_block(vertical_next_pt_px);
		if (check_coordinates_in_map(vars, vertical_next_pt_block) == 0)
			return (vertical_next_pt_px.reachable = 0, vertical_next_pt_px);
		vertical_first_pt_px = vertical_next_pt_px;
		vertical_first_pt_block = vertical_next_pt_block;
	}
	return (vertical_first_pt_px);
}*/