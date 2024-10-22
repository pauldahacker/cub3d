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
	if (keysym == LEFT)
		on_rotate_left(vars, ROTATE_SPEED);
	if (keysym == RIGHT)
		on_rotate_right(vars, ROTATE_SPEED);
	return (0);
}
