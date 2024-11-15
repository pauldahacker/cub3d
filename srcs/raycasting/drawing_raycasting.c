/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:20:19 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/15 21:17:53 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// see: https://permadi.com/1996/05/ray-casting-tutorial-9/
// 60 because our field of view (FOV) is 60
// How to calculate the distance from the wall ?
// tan formula in a triangle is: tan(angle) = opposite_side / adjacent_side
//                         <=>  adjacent_side = opposite_side / tan(angle)
// adjacent_side is our distance to the wall
// angle is our FOV angle which is 60° / 2 = 30°;
// Why divided by 2. Because we want to know the most straightforward ray, which
// is the one at the middle. Same for the opposite_side. The opposite_side is
// our whole projection plane. But we use only half of it.
// Thus: opposite_side = PROJ_PLANE_X / 2 = 320 / 2 = 160
/*
			The most straightforward ray is the one at the middle.
			To calculate it we use trigonometry in a triangle.
				As if it should:
__________ = Projection Plane = __________
\        /                      \    |
 \      /                        \   |
  \    /                          \  |
   \  /                            \ |
	\/     = FOV: angle = 60°       \|
*/
// The uppermost left ray (first one) will draw the first row

static double	calculate_projected_wall_height(t_vars *vars)
{
	double		actual_wall_height;
	double		projected_wall_height;
	t_player	*player;

	player = vars->game->player;
	actual_wall_height = BLOCK_SIZE;
	projected_wall_height = (actual_wall_height / player->distance_to_wall)
		* player->proj_plan.distance_player_pplan;
	return (projected_wall_height);
}

static void	set_calculus_projection_plan(t_proj *proj_plan,
	double projected_wall_height)
{
	proj_plan->wall_top_pos_y_in_pp = proj_plan->center_pp_y
		- projected_wall_height / 2;
	proj_plan->wall_lower_pos_y_in_pp = proj_plan->center_pp_y
		+ projected_wall_height / 2;
	proj_plan->wall_top_pos_y_in_px = proj_plan->wall_top_pos_y_in_pp
		* WINDOW_Y / PROJ_PLANE_Y;
	proj_plan->wall_lower_pos_y_in_px = proj_plan->wall_lower_pos_y_in_pp
		* WINDOW_Y / PROJ_PLANE_Y;
}

//PP means PROJECTION_PLAN
//this function draws one column of our FOV, starting from (x;y)
static void	draw_raycasting(t_vars *vars, int *x, int *y)
{
	t_proj		proj_plan;
	t_player	*player;

	player = vars->game->player;
	set_calculus_projection_plan(&player->proj_plan,
		player->projected_wall_height);
	proj_plan = player->proj_plan;
	if (*x < WINDOW_X)
	{
		*y = 0;
		while (*y < WINDOW_Y)
		{
			if (*y < proj_plan.wall_top_pos_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, vars->game->ceiling_color);
			else if (*y >= proj_plan.wall_top_pos_y_in_px
				&& *y <= proj_plan.wall_lower_pos_y_in_px)
				draw_wall(vars, x, y);
			else if (*y > proj_plan.wall_top_pos_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, vars->game->floor_color);
			(*y)++;
		}
		(*x)++;
	}
}

static void	set_data_projection_plan(t_vars *vars)
{
	vars->game->player->proj_plan.length_column
		= round(WINDOW_X / PROJ_PLANE_X);
	vars->game->player->proj_plan.center_pp_y = PROJ_PLANE_Y / 2;
	vars->game->player->proj_plan.distance_player_pplan = ((PROJ_PLANE_X / 2)
			/ tan((FOV / 2) * PI / 180.0));
}

//60 is the total field of view in degrees.
//For example the human horizontal FOV is 135. But in a 3D game, it's usually
//considered as a 60 degrees angle horizontal FOV
//angle_start starts at the left of our FOV (example: 120)
//angle_end finishes at the right of our FOV (example: 60)
void	draw_every_ray(t_vars *vars)
{
	int			y;
	int			x;
	t_player	*player;

	player = vars->game->player;
	player->ray_angle = player->angle_start;
	player->subsequent_angle = FOV / PROJ_PLANE_X;
	if (player->angle_end >= 300.0)
		player->angle_end -= 360.0;
	set_data_projection_plan(vars);
	x = 0;
	y = 0;
	while (player->ray_angle > player->angle_end)
	{
		player->distance_to_wall = calculate_best_distance(vars);
		player->projected_wall_height = calculate_projected_wall_height(vars);
		draw_raycasting(vars, &x, &y);
		player->ray_angle -= player->subsequent_angle;
	}
	if (player->angle_end <= 0)
		player->angle_end += 360.0;
}
