/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/05 14:16:24 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_wall(t_vars *vars, int *x, int *y)
{
//	double	texture_x;
//	double	texture_y;
	
//	texture_x = fmod(vars->game->player->point_hit.x, 64);
//	printf("texture_x = %f\n", texture_x);
//	texture_y = *y % 64;
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