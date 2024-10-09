/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/09 17:31:06 by simarcha         ###   ########.fr       */
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
	double		angle_subsequent_ray;
	double		distance_to_wall;//the distance from the player to the wall
	
}	t_ray;

//raycasting_utils.c
double		rounded_down(double nb);
double		rounded_nearest_nb(double nb);
t_block		convert_pixel_to_block(t_block point);
int			ray_facing_up(double angle);
int			ray_facing_right(double angle);

void		check_horizontal_angle_value(t_ray *ray);
void		check_vertical_angle_value(t_ray *ray);
int			coordinates_in_map(char **map, t_block current);


//horizontal_instersection.c
t_block		horizontal_point_crossing_wall(char **map, t_ray *ray);
void		init_ray_for_test(t_ray *ray);

//vertical_instersection.c
t_block		vertical_point_crossing_wall(char **map, t_ray *ray);


#endif