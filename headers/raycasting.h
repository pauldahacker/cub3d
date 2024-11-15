/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:00:14 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/15 21:16:57 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

# define PROJ_PLANE_X	WINDOW_X
# define PROJ_PLANE_Y	WINDOW_Y
# define BLOCK_SIZE		64
# define FOV			60.0

typedef struct s_game		t_game;
typedef struct raycasting	t_player;
typedef struct s_vars		t_vars;

//PP means PROJECTION_PLAN
typedef struct projection
{
	double	center_pp_y;
	double	wall_top_pos_y_in_px;
	double	wall_lower_pos_y_in_px;
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
int			ray_facing_up(double angle);
int			ray_facing_right(double angle);
int			check_coordinates_in_map(t_vars *vars, t_block current);

//horizontal_instersection.c
t_block		horizontal_point_crossing_wall(t_vars *vars);

//vertical_instersection.c
t_block		vertical_point_crossing_wall(t_vars *vars);

//calculate_best_distance.c
t_block		convert_pixel_to_block(t_block point);
double		calculate_best_distance(t_vars *vars);
t_block		return_intersection(t_vars *vars, double angle);

//draw_wall.c
void		draw_every_ray(t_vars *vars);

//checking_calculating_next_point.c
int			wall_not_in_diagonal(t_vars *vars, t_block current);

#endif