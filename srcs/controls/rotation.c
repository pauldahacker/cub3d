/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:44:25 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/11 14:37:02 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	increment_angle(double angle, double to_add)
{
	double	res;

	res = angle + to_add;
	if (res >= 360)
		return (res - 360);
	if (angle + to_add < 0)
		return (res + 360);
	return (res);
}

int	on_rotate_left(t_vars *vars, int speed)
{
	t_player	*player;

	if (!speed || speed > 360)
		return (0);
	player = vars->game->player;
	player->middle_fov_angle = increment_angle(player->middle_fov_angle,
			speed);
	player->angle_start = increment_angle(player->angle_start, speed);
	player->angle_end = increment_angle(player->angle_end, speed);
	return (0);
}

int	on_rotate_right(t_vars *vars, int speed)
{
	t_player	*player;

	if (!speed || speed > 360)
		return (0);
	player = vars->game->player;
	player->middle_fov_angle = increment_angle(player->middle_fov_angle,
			-speed);
	player->angle_start = increment_angle(player->angle_start, -speed);
	player->angle_end = increment_angle(player->angle_end, -speed);
	return (0);
}
