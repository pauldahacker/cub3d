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
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_vars *vars)
{
	//(void)vars;
	printf("Pressed key : %d\n", keysym);
	if (keysym == ESC)
		on_destroy(vars);
	return (0);
}
