/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finding_coordinate_horizontal_intersection.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:25:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/25 18:04:15 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//if the ray is facing up

typedef struct s_point
{
	x;
	y;
}	t_point;

//we need thee function to know if the ray is facing up or down
//this function returns 1 if is going up, 0 if it's going down
int	ray_facing_up(t_ray *ray)
{
	if (ray->ray_from_player_y <= ray->pos_y)
		return (1);
	else
		return (0);
}

//We want to convert the position of our character (=player) that we have in 
//pixel into cubs unit.
double	find_coordinate(t_ray *ray)
{
	t_point	a;
	
	if (ray_facing_up(ray) == 1)
		a.y = rounded_down(ray->pos_y / 64) * 64 - 1;
	else
		a.y = rounded_down(ray->pos_y / 64) * 64 + 64;
	
}