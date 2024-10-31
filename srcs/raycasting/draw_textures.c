/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/31 18:46:45 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_wall(t_vars *vars, int *x, int *y)
{
	// double	texture_x;
	// double	texture_y;

	// texture_x = *x % 64;
	// texture_y = *y % 64;
	if (ray_facing_up(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == true)
		my_mlx_pixel_put(*vars, *x, *y, STANDARD_GREY);//FACE SUD
	else if (ray_facing_up(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == true)
		my_mlx_pixel_put(*vars, *x, *y, BROWN);//FACE NORD
	else if (ray_facing_right(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == false)
		my_mlx_pixel_put(*vars, *x, *y, WHITE);//FACE OUEST
	else if (ray_facing_right(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == false)
		my_mlx_pixel_put(*vars, *x, *y, SILVER_GREY);//FACE EST
}

// void	draw_ceiling(t_vars *vars, int *x, int *y)
// {
	
// }

// void	draw_floor(t_vars *vars, int *x, int *y)
// {
	
// }