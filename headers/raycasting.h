/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/04 13:37:30 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define PROJECTION_PLANE_X 320
# define PROJECTION_PLANE_Y 200
# define BLOCK_SIZE			64

typedef struct s_game t_game;

//How do we code the map?
//It should be an array of int with the coordinates x and y
//I named it t_block because this is the unit that we use
//block[x][y] is one cell of our map
typedef struct s_block
{
	double	x;
	double	y;
}	t_block;

typedef struct raycasting
{
	double		pos_x;//player position in abscissa. The unit are the pixels!
	double		pos_y;//player position in ordinate. The unit are the pixels!
	double		angle;//angle (in degrees) of our ray starting from the abscissa axis 0 ≤ angle ≤360
	double		distance_to_wall;//the distance from the player to the wall
	
	// double		fov;//angle of player's field of view (=> should be in radian ?)
	//double	pov;
}	t_ray;

//raycasting_utils.c
double		rounded_down(double nb);
double		rounded_nearest_nb(double nb);
t_block		convert_pixel_to_block(t_block point);

#endif