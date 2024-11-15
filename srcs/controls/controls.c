/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   controls.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: simarcha <simarcha@student.42barcelona.	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/23 15:35:20 by pde-masc		  #+#	#+#			 */
/*   Updated: 2024/09/24 17:40:53 by simarcha		 ###   ########.fr	   */
/*																			*/
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
	if (keysym == ESC)
		on_destroy(vars);
	else if (keysym == W_KEY)
		vars->keys.w = 1;
	else if (keysym == A_KEY)
		vars->keys.a = 1;
	else if (keysym == S_KEY)
		vars->keys.s = 1;
	else if (keysym == D_KEY)
		vars->keys.d = 1;
	else if (keysym == LEFT)
		vars->keys.left = 1;
	else if (keysym == RIGHT)
		vars->keys.right = 1;
	return (0);
}

int	on_keyrelease(int keysym, t_vars *vars)
{
	if (keysym == W_KEY)
		vars->keys.w = 0;
	else if (keysym == A_KEY)
		vars->keys.a = 0;
	else if (keysym == S_KEY)
		vars->keys.s = 0;
	else if (keysym == D_KEY)
		vars->keys.d = 0;
	else if (keysym == LEFT)
		vars->keys.left = 0;
	else if (keysym == RIGHT)
		vars->keys.right = 0;
	return (0);
}

int	update_player(t_vars *vars)
{
	if (vars->keys.w)
		on_move_up(vars, MOVEMENT_SPEED);
	if (vars->keys.a)
		on_move_left(vars, MOVEMENT_SPEED);
	if (vars->keys.s)
		on_move_down(vars, MOVEMENT_SPEED);
	if (vars->keys.d)
		on_move_right(vars, MOVEMENT_SPEED);
	if (vars->keys.left)
		on_rotate_left(vars, ROTATE_SPEED);
	if (vars->keys.right)
		on_rotate_right(vars, ROTATE_SPEED);
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
	return (0);
}
