/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_angle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:34:01 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/09 15:49:23 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_horizontal_angle_value(t_ray *ray)
{
	int	rest;

	rest = (int)rounded_nearest_nb(ray->angle) % 180;
	if (rest == 180)
		ray->angle = 181;
	else if (rest == 0)
		ray->angle = 1;
}

/*void	check_vertical_angle_value(t_ray *ray)
{
	if (ray->angle == 180)
		ray->angle = 181;
	else if (ray->angle == 0)
		ray->angle = 1;
}*/