/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_every_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:15:32 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/13 17:41:30 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
//why 60? 60 is the total field of view angle.
//For example the human horizontal FOV is 135. But in a 3D game, it's usually
//considered as a 60 degrees angle horizontal FOV
void	draw_every_ray(t_vars *vars)
{
	double	alpha_angle;//this angle will switch every time until reaching player->angle_end
	double	subsequent_angle;
	t_block	distance_to_px;
	
	alpha_angle = vars->game->player->angle_start;
	subsequent_angle = 60 / PROJECTION_PLANE_X;
	while (alpha_angle <  vars->game->player->angle_end)
	{
		distance_to_px = calculate_best_distance(vars, vars->game->player->initial_angle);
		my_mlx_pixel_put(*vars, distance_to_px.x, distance_to_px.y, GREY);
		alpha_angle += subsequent_angle;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
}
*/