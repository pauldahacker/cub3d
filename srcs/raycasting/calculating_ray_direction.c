/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculating_ray_direction.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:55:28 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/09 19:43:20 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	init_player_for_test(t_player *ray)
// {
// 	ray->pos_x = 90;
// 	ray->pos_y = 224;
// 	ray->angle = 60;
// }

// void	calculating_ray_direction(t_player *ray)
// {
// 	int		x;
// 	double	camera_x;
// 	double	ray_dir_x;
// 	double	ray_dir_y;

// 	x = 0;
// 	while (x < WINDOW_X)
// 	{
// 		camera_x = 2 * x /(double)WINDOW_X - 1;
// 		ray_dir_x = ray->pos_x + plane_x * camera_x;		
// 		ray_dir_y = ray->pos_y + plane_y * camera_x;		
// 		x++;
// 	}
// }