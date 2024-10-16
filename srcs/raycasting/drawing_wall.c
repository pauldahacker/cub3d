/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:20:19 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/16 18:26:46 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//see: https://permadi.com/1996/05/ray-casting-tutorial-9/
//60 because our field of view (FOV) is 60

double	calculate_projected_wall_height(double distance_to_wall)
{
	double	actual_wall_height;
	double	distance_player_projection_plane;
	double	projected_wall_height;

	actual_wall_height = BLOCK_SIZE;
	distance_player_projection_plane = ((PROJECTION_PLANE_X / 2) / tan ((60 / 2) * PI / 180));
	projected_wall_height = (actual_wall_height / distance_to_wall) * distance_player_projection_plane;
	projected_wall_height = rounded_nearest_nb(projected_wall_height);
	printf("projected_wall_height = %f\n", projected_wall_height);
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
				my_mlx_pixel_put(*vars, *x, *y, ELECTRIC_BLUE);//imprimer le plafond d'une couleur BLEU
			else if (*y >= wall_top_position_y_in_px && *y <= wall_lower_position_y_in_px)
				my_mlx_pixel_put(*vars, *x, *y, GREY);//imprimer le plafond d'une couleur NOIRE
			else if (*y > wall_top_position_y_in_px)// ca veut dire que l'on est en dessous du mur
				my_mlx_pixel_put(*vars, *x, *y, WHITE);//imprimer le sol d'une couleur blanche
			(*y)++;
		}
		(*x)++;
		if (*x % length_column == 0)
			break ;
	}
}

//why 60? 60 is the total field of view angle.
//For example the human horizontal FOV is 135. But in a 3D game, it's usually
//considered as a 60 degrees angle horizontal FOV
void	draw_every_ray(t_vars *vars)
{
	double	alpha_angle;//this angle will switch every time until reaching player->angle_end
	double	distance_to_wall;
	double	projected_wall_height;
	int		y;
	int		x;

	alpha_angle = vars->game->player->angle_start;
	printf("vars->game->player->angle_start = %f\n", vars->game->player->angle_start);
	x = 0;
	y = 0;
	while (alpha_angle > vars->game->player->angle_end)
	{
		distance_to_wall = calculate_best_distance(vars, alpha_angle);
		projected_wall_height = calculate_projected_wall_height(distance_to_wall);
		if (projected_wall_height > 150.0)
			printf("x = %i y = %i\n", x, y);
		draw_wall(vars, projected_wall_height, &x, &y);
		alpha_angle -= vars->game->player->subsequent_angle;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
}






























/*void	draw_wall(t_vars *vars, double projected_wall_height)
{
	double	center_projection_plan_y;
	double	length_column;
	double	wall_top_position_y;
	double	wall_lower_position_y;
	int		i;//x_lines
	int		j;//y_columns

	length_column = rounded_nearest_nb(WINDOW_X / PROJECTION_PLANE_X);
	center_projection_plan_y = PROJECTION_PLANE_Y / 2;
	wall_top_position_y = center_projection_plan_y - projected_wall_height / 2;
	wall_lower_position_y = center_projection_plan_y + projected_wall_height / 2;
	while (i < PROJECTION_PLANE_X)
	{
		while (j < PROJECTION_PLANE_Y)
		{
			if (j < wall_top_position_y)
				//imprimer le plafond d'une couleur BLEU
			if (j >= wall_top_position_y && j <= wall_lower_position_y)
				//imprimer le plafond d'une couleur NOIRE
			else // ca veut dire que l'on est en dessous du mur
				;//imprimer le sol d'une couleur blanche
			y++;
		}
		i++;
	}
//	my_mlx_pixel_put(*vars, distance_to_px.x, distance_to_px.y, WHITE);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);

}*/