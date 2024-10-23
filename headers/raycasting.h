/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/23 16:32:06 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define PROJECTION_PLANE_X	320
# define PROJECTION_PLANE_Y	200
# define BLOCK_SIZE			32

typedef struct s_game		t_game;
typedef struct raycasting	t_player;
typedef struct s_vars		t_vars;

//How do we code the map?
//It should be an array of int with the coordinates x and y
//I named it t_point because this is the unit that we use
//block[x][y] is one cell of our map
typedef struct s_block
{
	double	x;
	double	y;
	bool	reachable;
}	t_point;

//raycasting_utils.c
double		rounded_down(double nb);
double		rounded_nearest_nb(double nb);
t_point		convert_pixel_to_block(t_point point);
int			ray_facing_up(double angle);
int			ray_facing_right(double angle);

void		check_horizontal_angle_value(t_player *ray);
void		check_vertical_angle_value(t_player *ray);
int			check_coordinates_in_map(t_vars *vars, t_point current);

//horizontal_instersection.c
t_point		horizontal_point_crossing_wall(t_vars *vars, double ray_angle);
void		init_player_for_test(t_player *ray);

//vertical_instersection.c
t_point		vertical_point_crossing_wall(t_vars *vars, double ray_angle);

//double		calculate_best_distance(t_vars *vars, double angle);
t_point		return_intersection(t_vars *vars, double angle);
double		calculate_best_distance(t_vars *vars, double angle);
void		draw_every_ray(t_vars *vars);
//double		calculate_projected_wall_height(t_vars *vars, double distance_to_wall);

double		ft_abs(double number);

#endif