/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:41:13 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/04 15:41:15 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_in_wall(t_game *game, double pos_x, double pos_y)
{
	double	x;
	double	y;

	x = pos_x / BLOCK_SIZE;
	y = pos_y / BLOCK_SIZE;
	if (game->map[(int)(y - 0.25)][(int)(x - 0.25)] == '1'
		|| game->map[(int)(y + 0.25)][(int)(x - 0.25)] == '1'
			|| game->map[(int)(y - 0.25)][(int)(x + 0.25)] == '1'
				|| game->map[(int)(y + 0.25)][(int)(x + 0.25)] == '1')
		return (1);
	return (0);
}

double	return_x_increment(t_vars *vars, double angle, int speed)
{
	double	pos_x;

	pos_x = (vars->game->player->pos_x + cos(angle * PI / 180) * speed);
	while (speed && is_in_wall(vars->game, pos_x, vars->game->player->pos_y))
		pos_x = (vars->game->player->pos_x + cos(angle * PI / 180) * --speed);
	return (cos(angle * PI / 180) * speed);
}

double	return_y_increment(t_vars *vars, double angle, int speed)
{
	double	pos_y;

	pos_y = (vars->game->player->pos_y - sin(angle * PI / 180) * speed);
	while (speed && is_in_wall(vars->game, vars->game->player->pos_x, pos_y))
		pos_y = (vars->game->player->pos_y - sin(angle * PI / 180) * --speed);
	return (-sin(angle * PI / 180) * speed);
}
