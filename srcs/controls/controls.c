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

int	on_move_up(t_vars *vars)
{
	int		player_x;
	int		player_y;
	char	**map;

	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y;
	map = vars->game->map;
	printf("Player coordinates:x: %f\ny: %f\n", vars->game->player->pos_x, vars->game->player->pos_y);
	if ((player_y - MOVEMENT_SPEED) > 0 && map[(player_y - MOVEMENT_SPEED) / 64][player_x / 64] != '1')
		vars->game->player->pos_y = vars->game->player->pos_y - MOVEMENT_SPEED;
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_left(t_vars *vars)
{
	int		player_x;
	int		player_y;
	char	**map;

	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y;
	map = vars->game->map;
	if ((player_x - MOVEMENT_SPEED) > 0 && map[player_y / 64][(player_x - MOVEMENT_SPEED) / 64] != '1')
		vars->game->player->pos_x = vars->game->player->pos_x - MOVEMENT_SPEED;
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_down(t_vars *vars)
{
	int		player_x;
	int		player_y;
	char	**map;

	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y;
	map = vars->game->map;
	if ((player_y + MOVEMENT_SPEED) / 64 < vars->game->n_rows && map[(player_y + MOVEMENT_SPEED) / 64][player_x / 64] != '1')
		vars->game->player->pos_y = vars->game->player->pos_y + MOVEMENT_SPEED;
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_right(t_vars *vars)
{
	int		player_x;
	int		player_y;
	char	**map;

	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y;
	map = vars->game->map;
	printf("Player coordinates:x: %f\ny: %f\n", vars->game->player->pos_x, vars->game->player->pos_y);
	if ((player_x + MOVEMENT_SPEED) / 64 < vars->game->n_cols && map[player_y / 64][(player_x + MOVEMENT_SPEED) / 64] != '1')
		vars->game->player->pos_x = vars->game->player->pos_x + MOVEMENT_SPEED;
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
		on_move_up(vars);
	if (keysym == A)
		on_move_left(vars);
	if (keysym == S)
		on_move_down(vars);
	if (keysym == D)
		on_move_right(vars);
	return (0);
}
