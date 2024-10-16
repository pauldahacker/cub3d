/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_every_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:15:32 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/16 16:38:03 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	check_pixels_value(t_vars *vars, t_block *point)
{
	t_block	max_vision;

	max_vision.x = (vars->game->n_rows - 1) * BLOCK_SIZE;
	max_vision.y = (vars->game->n_cols - 1) * BLOCK_SIZE;
	if (point->x < 0)
		point->x -= point->x;
	else if (point->y < 0)
		point->y -= point->y;
	if (point->x > max_vision.x)
		point->x = max_vision.x;
	else if (point->y > max_vision.y)
		point->y = max_vision.y;
}*/

//why 60? 60 is the total field of view angle.
//For example the human horizontal FOV is 135. But in a 3D game, it's usually
//considered as a 60 degrees angle horizontal FOV
/*void	draw_every_ray(t_vars *vars)
{
	double	alpha_angle;//this angle will switch every time until reaching player->angle_end
	double	subsequent_angle;
	t_block	distance_to_px;
	int		i = 0;
	
	alpha_angle = vars->game->player->angle_start;
	printf("vars->game->player->angle_start = %f\n", vars->game->player->angle_start);
//	subsequent_angle = 60.0 / 320.0;// PROJECTION_PLANE_X;
//	printf("subsequent_angle = %f\n", subsequent_angle);
	while (alpha_angle > vars->game->player->angle_end)
	{
		distance_to_px = calculate_best_distance(vars, alpha_angle);
		printf("distance_to_px.x = %f distance_to_px.y = %f\n", distance_to_px.x, distance_to_px.y);
		check_pixels_value(vars, &distance_to_px);
		my_mlx_pixel_put(*vars, distance_to_px.x, distance_to_px.y, WHITE);
		alpha_angle -= subsequent_angle;
		printf("alpha_angle = %f\n", alpha_angle);
		i++;
		if (i > 500)
			break ;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
}*/