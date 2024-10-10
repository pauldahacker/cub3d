/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/10 12:33:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define PROJECTION_PLANE_X 320
# define PROJECTION_PLANE_Y 200
# define BLOCK_SIZE			64

typedef struct s_game		t_game;
typedef struct raycasting	t_player;
typedef struct s_vars		t_vars;


//How do we code the map?
//It should be an array of int with the coordinates x and y
//I named it t_block because this is the unit that we use
//block[x][y] is one cell of our map
typedef struct s_block
{
	double	x;
	double	y;
}	t_block;

//raycasting_utils.c
double		rounded_down(double nb);
double		rounded_nearest_nb(double nb);
t_block		convert_pixel_to_block(t_block point);
int			ray_facing_up(double angle);
int			ray_facing_right(double angle);

void		check_horizontal_angle_value(t_player *ray);
void		check_vertical_angle_value(t_player *ray);
int			check_coordinates_in_map(t_vars *vars, t_block current);


//horizontal_instersection.c
t_block		horizontal_point_crossing_wall(t_vars *vars);
void		init_player_for_test(t_player *ray);

//vertical_instersection.c
t_block		vertical_point_crossing_wall(t_vars *vars);


#endif