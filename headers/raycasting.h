/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/11 19:22:56 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define PROJ_PLANE_X	320
# define PROJ_PLANE_Y	200
# define BLOCK_SIZE		64

typedef struct s_game		t_game;
typedef struct raycasting	t_player;
typedef struct s_vars		t_vars;

//PP means PROJECTION_PLAN
typedef struct projection
{
	double	center_pp_y;
	double	wall_top_pos_y_in_px;
	double	wall_lower_pos_y_in_px;
	double	wall_upper_left_x_in_px;//this is the start of the block
	double	wall_upper_right_x_in_px;//this is the start of it's following block
	double	wall_top_pos_y_in_pp;
	double	wall_lower_pos_y_in_pp;
	double	distance_player_pplan;
	int		length_column;
}	t_proj;

//How do we code the map?
//It should be an array of int with the coordinates x and y
//I named it t_block because this is the unit that we use
//block[x][y] is one cell of our map
typedef struct s_block
{
	double	x;
	double	y;
	bool	reachable;
}	t_block;

//raycasting_utils.c
double		rounded_down(double nb);
double		rounded_nearest_nb(double nb);
int			ray_facing_up(double angle);
int			ray_facing_right(double angle);
int			check_coordinates_in_map(t_vars *vars, t_block current);

//horizontal_instersection.c
t_block		horizontal_point_crossing_wall(t_vars *vars, double ray_angle);

//vertical_instersection.c
t_block		vertical_point_crossing_wall(t_vars *vars, double ray_angle);

//calculate_best_distance.c
t_block		convert_pixel_to_block(t_block point);
double		ft_abs(double number);
double		calculate_best_distance(t_vars *vars, double angle);
t_block		return_intersection(t_vars *vars, double angle);

//draw_wall.c
void		draw_every_ray(t_vars *vars);

#endif