/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_raycasting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:20:19 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/31 20:07:18 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//see: https://permadi.com/1996/05/ray-casting-tutorial-9/
//60 because our field of view (FOV) is 60
//How to calculate the distance from the wall ?
//tan formula in a triangle is: tan(angle) = opposite_side / adjacent_side
//                        <=>  adjacent_side = opposite_side / tan(angle)
//adjacent_side is our distance to the wall
//angle is our FOV angle which is 60° / 2 = 30°;
//Why divided by 2. Because we want to know the most straightforward ray, which
//is the one at the middle. Same for the opposite_side. The opposite_side is 
//our whole projection plane. But we use only half of it.
//Thus: opposite_side = PROJ_PLANE_X / 2 = 320 / 2 = 160
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

//The uppermost left ray (first one) will draw the first row

static double	calculate_projected_wall_height(t_vars *vars,
	double dist_to_wall)
{
	double	actual_wall_height;
	double	projected_wall_height;

	actual_wall_height = BLOCK_SIZE;
	projected_wall_height = (actual_wall_height / dist_to_wall)
		* vars->game->player->proj_plan.distance_player_pplan;
	projected_wall_height = rounded_nearest_nb(projected_wall_height);
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
static void	draw_raycasting(t_vars *vars, double projected_wall_height, int *x,
	int *y)
{
	t_proj	proj_plan;

	proj_plan = vars->game->player->proj_plan;
	set_calculus_projection_plan(&proj_plan, projected_wall_height);
	while (*x < WINDOW_X)
	{
		*y = 0;
		while (*y < WINDOW_Y)
		{
			if (*y < proj_plan.wall_top_pos_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, vars->game->ceiling_color);
				//draw_ceiling(vars, *x, *y, vars->game->ceiling_color);
			else if (*y >= proj_plan.wall_top_pos_y_in_px
				&& *y <= proj_plan.wall_lower_pos_y_in_px)
				draw_wall(vars, x, y);
			else if (*y > proj_plan.wall_top_pos_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, vars->game->floor_color);
				//draw_floor(vars, *x, *y, vars->game->floor_color);
			(*y)++;		
		}
		(*x)++;
		if (*x % proj_plan.length_column == 0)
			break ;
	}
}

static void	set_data_projection_plan(t_vars *vars)
{
	vars->game->player->proj_plan.length_column
		= rounded_nearest_nb(WINDOW_X / PROJ_PLANE_X);
	vars->game->player->proj_plan.center_pp_y = PROJ_PLANE_Y / 2;
	vars->game->player->proj_plan.distance_player_pplan = ((PROJ_PLANE_X / 2)
			/ tan((60 / 2) * PI / 180.0));
}

//60 is the total field of view in degrees.
//For example the human horizontal FOV is 135. But in a 3D game, it's usually
//considered as a 60 degrees angle horizontal FOV
//angle_start starts at the left of our FOV (example: 120)
//angle_end finishes at the right of our FOV (example: 60)
void	draw_every_ray(t_vars *vars)
{
	double	dist_to_wall;
	double	projected_wall_height;
	int		y;
	int		x;
	double	ray_angle;

	ray_angle = vars->game->player->angle_start;
	if (vars->game->player->angle_end >= 300.0)
		vars->game->player->angle_end -= 360.0;
	set_data_projection_plan(vars);
	x = 0;
	y = 0;
	while (ray_angle > vars->game->player->angle_end)
	{
		vars->game->player->ray_angle = ray_angle;
		dist_to_wall = calculate_best_distance(vars, ray_angle);
		projected_wall_height = calculate_projected_wall_height(vars,
				dist_to_wall);
		draw_raycasting(vars, projected_wall_height, &x, &y);
		ray_angle -= vars->game->player->subsequent_angle;
	}
	if (vars->game->player->angle_end <= 0)
		vars->game->player->angle_end += 360.0;
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
}
