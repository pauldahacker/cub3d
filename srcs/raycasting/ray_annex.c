/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_annex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:17:49 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/12 18:38:29 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
int	wall_not_in_ascending_diagonal(t_vars *vars, t_block current)
{
	char	**map;

	map = vars->game->map;
	if (ray_facing_up(vars->game->player->ray_angle) == 1)
	{
		if ((int)current.y < vars->game->n_rows - 1 && (int)current.x < vars->game->n_cols &&
		(map[(int)current.y][(int)current.x] == 'V' || map[(int)current.y][(int)current.x] == '0') &&
		map[(int)current.y + 1][(int)current.x] == '1' &&
		map[(int)current.y][(int)current.x + 1] == '1' &&
		(map[(int)current.y + 1][(int)current.x + 1] == 'V' || map[(int)current.y + 1][(int)current.x + 1] == '0'))
			return (0);
	}
	else
	{
		if ((int)current.y > 0 && (int)current.x > 0 &&
		(map[(int)current.y][(int)current.x] == 'V' || map[(int)current.y][(int)current.x] == '0') &&
		map[(int)current.y - 1][(int)current.x] == '1' &&
		map[(int)current.y][(int)current.x - 1] == '1' &&
		(map[(int)current.y - 1][(int)current.x - 1] == 'V' || map[(int)current.y - 1][(int)current.x - 1] == '0')
		)
			return (0);
	}
	return (1);
}
