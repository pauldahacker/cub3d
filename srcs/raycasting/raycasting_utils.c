/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/13 19:29:07 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//we need a function to know if the ray is facing up or down
//this function returns 1 if is going up, 0 if it's going down
//how to know if the angle is facing up ?
//We start from the abscissa axis and we go anticlockwise.
//We know that is facing up if the angle goes from 0° ≤ angle < 180 (% 360)
int	ray_facing_up(double angle)
{
	if (angle >= 0.0 && angle < 180.0)
		return (1);
	else
		return (0);
}

//we need thee function to know if the ray is facing right or left
//this function returns 1 if is going right, 0 if it's going left
//how to know if the angle is facing right ?
//We start from the abscissa axis and we go anticlockwise.
//Basically, we know that angle is facing right if the angle goes from 
//-90° ≤ angle ≤ 90 (everything % 360)
//We reduce by 360 in draw_every_ray function, so we have to check -90.0 as well
int	ray_facing_right(double angle)
{
	if ((angle >= -90.0 && angle < 90.0)
		|| (angle >= 270.0 && angle <= 360.0))
		return (1);
	else
		return (0);
}

int	check_coordinates_in_map(t_vars *vars, t_block current)
{
	if (current.y < 0 || current.y > vars->game->n_rows - 1
		|| current.x < 0 || current.x > vars->game->n_cols)
		return (0);
	return (1);
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
//If the ray is facing up, we check the walls with reference the upper left one
//else, we check the walls with reference the lower right one
//if the configuration is not set in ascending diagonal like above, we return 1
int	wall_not_in_ascending_diagonal(t_vars *vars, t_block current)
{
	char	**map;

	map = vars->game->map;
	if (ray_facing_up(vars->game->player->ray_angle) == 1
		&& ray_facing_right(vars->game->player->ray_angle) == 0)
	{
		if ((int)current.y < vars->game->n_rows - 1
			&& (int)current.x < vars->game->n_cols
			&& (map[(int)current.y][(int)current.x] == 'V')
			&& map[(int)current.y + 1][(int)current.x] == '1'
			&& map[(int)current.y][(int)current.x + 1] == '1'
			&& (map[(int)current.y + 1][(int)current.x + 1] == 'V'))
			return (0);
	}
	else if (ray_facing_up(vars->game->player->ray_angle) == 0
		&& ray_facing_right(vars->game->player->ray_angle) == 1)
	{
		if ((int)current.y > 0 && (int)current.x > 0
			&& (map[(int)current.y][(int)current.x] == 'V')
			&& map[(int)current.y - 1][(int)current.x] == '1'
			&& map[(int)current.y][(int)current.x - 1] == '1'
			&& (map[(int)current.y - 1][(int)current.x - 1] == 'V'))
			return (0);
	}
	return (1);
}
