/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/10 14:55:31 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_texture(t_vars *vars, int x, int y, t_texture tex)
{
	int	color;
	
	color = BLACK;
	(void)tex;
	my_mlx_pixel_put(*vars, x, y, color);
	if (y == vars->game->player->proj_plan.wall_top_pos_y_in_px)
	{
		my_mlx_pixel_put(*vars, x, y, WHITE);
		printf("y = %i\n", y);
	}
}

void	draw_permadi_wall(t_vars *vars, int x, int y, t_texture tex)
{
	int			texture_offset_x;
	int			texture_y;
	int			start_y;
	int			end_y;
	t_player	*player;
	int			color;

	player = vars->game->player;
	if (vars->game->player->horizontal_distance_chosen == true)
		texture_offset_x = (int)vars->game->player->point_hit.x % tex.width;
	else
		texture_offset_x = (int)vars->game->player->point_hit.x % tex.height;
	start_y = vars->game->player->proj_plan.wall_top_pos_y_in_px;
	end_y = vars->game->player->proj_plan.wall_lower_pos_y_in_px;
	while (start_y < end_y)
	{
		texture_y = (y - start_y) * BLOCK_SIZE / player->projected_wall_height;
		color = get_color_from_texture(&tex, texture_offset_x, texture_y);
		my_mlx_pixel_put(*vars, x, y, color);
		y++;
	}
}

void	draw_wall(t_vars *vars, int *x, int *y)
{
	if (ray_facing_up(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_permadi_wall(vars, *x, *y, vars->south_tex);
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