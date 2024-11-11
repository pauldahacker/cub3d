/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:45:19 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/11 14:36:56 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_move_up(t_vars *vars, int speed)
{
	double	angle;

	angle = vars->game->player->middle_fov_angle;
	vars->game->player->pos_x += return_x_increment(vars, angle, speed);
	vars->game->player->pos_y += return_y_increment(vars, angle, speed);
	return (0);
}

int	on_move_left(t_vars *vars, int speed)
{
	double	angle;

	angle = vars->game->player->middle_fov_angle + 90;
	if (angle >= 360)
		angle -= 360;
	vars->game->player->pos_x += return_x_increment(vars, angle, speed);
	vars->game->player->pos_y += return_y_increment(vars, angle, speed);
	return (0);
}

int	on_move_down(t_vars *vars, int speed)
{
	double	angle;

	angle = vars->game->player->middle_fov_angle + 180;
	if (angle >= 360)
		angle -= 360;
	vars->game->player->pos_x += return_x_increment(vars, angle, speed);
	vars->game->player->pos_y += return_y_increment(vars, angle, speed);
	return (0);
}

int	on_move_right(t_vars *vars, int speed)
{
	double	angle;

	angle = vars->game->player->middle_fov_angle - 90;
	if (angle < 0)
		angle += 360;
	vars->game->player->pos_x += return_x_increment(vars, angle, speed);
	vars->game->player->pos_y += return_y_increment(vars, angle, speed);
	return (0);
}
