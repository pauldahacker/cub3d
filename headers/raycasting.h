/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/27 19:18:31 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define PROJECTION_PLANE_X 320
# define PROJECTION_PLANE_Y 200

typedef struct s_grid
{
	double	x;
	double	y;
}	t_grid;

typedef struct raycasting
{
	double		pos_x;//player position in abscissa. The unit are the pixels!
	double		pos_y;//player position in ordinate. The unit are the pixels!
	double		dir_x;//player direction/orientation in abscissa
	double		dir_y;//player direction/orientation in ordinate
	double		plane_x;//camera plane of the player
	double		plane_y;//camera plane of the player
	
	double		ray_from_player_x;//distance from player & the end of the ray
	double		ray_from_player_y;//distance from player & the end of the ray

	double		angle;//angle of our ray starting from the abscissa axis
	
	// double		fov;//angle of player's field of view (=> should be in radian ?)
	// double		ray_x;//position of the pixel for the first ray of our podouble of view
	// double		ray_x_prime;//position of the pixel for the last ray of our pov
	// double		ray_y;//position of the pixel for the first ray of our podouble of view
	// double		ray_y_prime;//position of the pixel for the last ray of our pov
	
	
}	t_ray;

//raycasting_utils.c
double		rounded_down(double position);
t_grid		convert_pixel_to_grid(t_grid point);



#endif