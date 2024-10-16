/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:35:20 by pde-masc          #+#    #+#             */
/*   Updated: 2024/09/24 17:40:53 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	on_destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	free(vars->mlx_ptr);
	destroy_game(vars->game);
	exit(0);
	return (0);
}

int	on_move_up(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed)
		return (0);
	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y - attempted_speed;
	j = -1;
	while (++j < 32)
	{
		i = -1;
		while (++i < 32)
		{
			if (vars->game->map[(player_y + j) / 64][(player_x + i) / 64] == '1')
				return (on_move_up(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_y = vars->game->player->pos_y - attempted_speed;
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_left(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed)
		return (0);
	player_x = (int)vars->game->player->pos_x - attempted_speed;
	player_y = (int)vars->game->player->pos_y;
	j = -1;
	while (++j < 32)
	{
		i = -1;
		while (++i < 32)
		{
			if (vars->game->map[(player_y + j) / 64][(player_x + i) / 64] == '1')
				return (on_move_left(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_x = vars->game->player->pos_x - attempted_speed;
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_down(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed)
		return (0);
	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y + attempted_speed;
	j = -1;
	while (++j < 32)
	{
		i = -1;
		while (++i < 32)
		{
			if (vars->game->map[(player_y + j) / 64][(player_x + i) / 64] == '1')
				return (on_move_down(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_y = vars->game->player->pos_y + attempted_speed;
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_right(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed)
		return (0);
	player_x = (int)vars->game->player->pos_x + attempted_speed;
	player_y = (int)vars->game->player->pos_y;
	j = -1;
	while (++j < 32)
	{
		i = -1;
		while (++i < 32)
		{
			if (vars->game->map[(player_y + j) / 64][(player_x + i) / 64] == '1')
				return (on_move_right(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_x = vars->game->player->pos_x + attempted_speed;
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_keypress(int keysym, t_vars *vars)
{
	//(void)vars;
	printf("Pressed key : %d\n", keysym);
	if (keysym == ESC)
		on_destroy(vars);
	if (keysym == W)
		on_move_up(vars, MOVEMENT_SPEED);
	if (keysym == A)
		on_move_left(vars, MOVEMENT_SPEED);
	if (keysym == S)
		on_move_down(vars, MOVEMENT_SPEED);
	if (keysym == D)
		on_move_right(vars, MOVEMENT_SPEED);
	return (0);
}
