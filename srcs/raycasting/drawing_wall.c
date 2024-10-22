/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:20:19 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/22 17:46:26 by simarcha         ###   ########.fr       */
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
//Thus: opposite_side = PROJECTION_PLANE_X / 2 = 320 / 2 = 160
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

void	my_mlx_pixel_put(t_vars vars, int x, int y, int color)
{
	char	*dst;

	dst = vars.data.addr + (y * vars.data.line_length + x
			* (vars.data.bpp / 8));
	*(unsigned int *)dst = color;
}

double	calculate_projected_wall_height(double distance_to_wall)
{
	double	actual_wall_height;
	double	distance_player_projection_plane;
	double	projected_wall_height;

	actual_wall_height = BLOCK_SIZE;
	distance_player_projection_plane = ((PROJECTION_PLANE_X / 2) / tan((60 / 2) * PI / 180.0));
	projected_wall_height = (actual_wall_height / distance_to_wall) * distance_player_projection_plane;
	projected_wall_height = rounded_nearest_nb(projected_wall_height);
	return (projected_wall_height);
}

//PP means PROJECTION_PLAN
//this function draws one column of our FOV, starting from (x;y)
void	draw_wall(t_vars *vars, double projected_wall_height, int *x, int *y)
{
	double	center_projection_plan_y;
	double	wall_top_position_y_in_PP;
	double	wall_lower_position_y_in_PP;
	double	wall_top_position_y_in_px;
	double	wall_lower_position_y_in_px;
	int		length_column;

	length_column = rounded_nearest_nb(WINDOW_X / PROJECTION_PLANE_X);
	center_projection_plan_y = PROJECTION_PLANE_Y / 2;
	wall_top_position_y_in_PP = center_projection_plan_y - projected_wall_height / 2;
	wall_lower_position_y_in_PP = center_projection_plan_y + projected_wall_height / 2;
	wall_top_position_y_in_px = wall_top_position_y_in_PP * WINDOW_Y / PROJECTION_PLANE_Y;
	wall_lower_position_y_in_px = wall_lower_position_y_in_PP * WINDOW_Y / PROJECTION_PLANE_Y;
	while (*x < WINDOW_X)
	{
		*y = 0;
		while (*y < WINDOW_Y)
		{
			if (*y < wall_top_position_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, vars->game->ceiling_color);
			else if (*y >= wall_top_position_y_in_px && *y <= wall_lower_position_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, GREY);
			else if (*y > wall_top_position_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, vars->game->floor_color);
			(*y)++;
		}
		(*x)++;
		if (*x % length_column == 0)
			break ;
	}
}

//60 is the total field of view in degrees.
//For example the human horizontal FOV is 135. But in a 3D game, it's usually
//considered as a 60 degrees angle horizontal FOV
//angle_start starts at the left of our FOV (example: 120)
//angle_end finishes at the right of our FOV (example: 60)
void	draw_every_ray(t_vars *vars)
{
	double	distance_to_wall;
	double	projected_wall_height;
	int		y;
	int		x;
	double	ray_angle;

	ray_angle = vars->game->player->angle_start;
	x = 0;
	y = 0;
	if (vars->game->player->angle_end > 300.0)
		vars->game->player->angle_end -= 360.0;//I do this for E player's position
	printf("vars->game->player->angle_start = %f\n", vars->game->player->angle_start);
	printf("ray_angle = %f\n", ray_angle);
	printf("vars->game->player->angle_end = %f\n", vars->game->player->angle_end);
	while (ray_angle > vars->game->player->angle_end)
	{
		distance_to_wall = calculate_best_distance(vars, ray_angle);
		projected_wall_height = calculate_projected_wall_height(distance_to_wall);
		draw_wall(vars, projected_wall_height, &x, &y);
		ray_angle -= vars->game->player->subsequent_angle;
	}
	if (vars->game->player->angle_end > 300.0)
		vars->game->player->angle_end -= 360.0;//I do this for E player's position
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
}
