/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:47:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/14 20:26:30 by simarcha         ###   ########.fr       */
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
