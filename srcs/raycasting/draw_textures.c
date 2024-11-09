/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/09 13:46:31 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_texture(t_vars *vars, int x, int y, t_texture tex)
{
	int	color;
	
	color = BLACK;
	(void)tex;
	//printf("vars->game->player->projected_wall_height = %f\n", vars->game->player->projected_wall_height);
	my_mlx_pixel_put(*vars, x, y, color);
	if (y <= vars->game->player->proj_plan.wall_top_pos_y_in_px)
	{
		my_mlx_pixel_put(*vars, x, y, WHITE);
		printf("i = %i\n", x);
		if (x == 0)
			exit(0);
	}
}

void	draw_wall(t_vars *vars, int *x, int *y)
{
	if (ray_facing_up(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_texture(vars, *x, *y, vars->south_tex);
	else if (ray_facing_up(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_texture(vars, *x, *y, vars->north_tex);
	else if (ray_facing_right(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == false)
		draw_texture(vars, *x, *y, vars->west_tex);
	else if (ray_facing_right(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == false)
		draw_texture(vars, *x, *y, vars->east_tex);
}

// void	draw_ceiling(t_vars *vars, int *x, int *y)
// {
// }

// void	draw_floor(t_vars *vars, int *x, int *y)
// {
// }