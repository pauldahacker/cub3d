/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/12 11:12:36 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_texture(t_vars *vars, int x, int *y, t_texture tex)
{
	t_player		*player;
	unsigned int	color;
	int				pixel_offset;

	player = vars->game->player;
	if (player->former_block_touched.reachable == false)//it means that this is the first ray and former_block_touched is not set yet
		player->former_block_touched = player->block_touched;//we set it
	pixel_offset = (*y % 64) * tex.size_line + (x % 64) * (tex.bpp / 8);
	color = (tex.data[pixel_offset]) << 16 | (tex.data[pixel_offset + 1]) << 8
		|(tex.data[pixel_offset + 2]);
	if (rounded_down(player->former_block_touched.x) == rounded_down(player->block_touched.x)
			&& rounded_down(player->former_block_touched.y) == rounded_down(player->block_touched.y))
		my_mlx_pixel_put(*vars, x, *y, color);
	else
	{
		color = WHITE;
		while (*y <= player->proj_plan.wall_lower_pos_y_in_px + 1)
			my_mlx_pixel_put(*vars, x, (*y)++, color);
	}
	if (!(rounded_down(player->former_block_touched.x) == rounded_down(player->block_touched.x)))
	{
		player->proj_plan.wall_upper_left_x_in_px = player->former_block_touched.x;
		player->proj_plan.wall_upper_right_x_in_px = player->block_touched.x;
		player->horizontal_wall_size_in_px = player->proj_plan.wall_upper_right_x_in_px - player->proj_plan.wall_upper_left_x_in_px;
		// printf("EN XXXXXX: \nplayer->former_block_touched.x = %f\n", player->former_block_touched.x);
		// printf("player->block_touched.x = %f\n", player->block_touched.x);
		// printf("player->horizontal_wall_size_in_px = %f\n", player->horizontal_wall_size_in_px);
	}
	else if (!(rounded_down(player->former_block_touched.y) == rounded_down(player->block_touched.y)))
	{
		player->proj_plan.wall_upper_left_x_in_px = player->former_block_touched.x;
		player->proj_plan.wall_upper_right_x_in_px = player->block_touched.x;
		player->horizontal_wall_size_in_px = player->proj_plan.wall_upper_right_x_in_px - player->proj_plan.wall_upper_left_x_in_px;
		// printf("EN YYYYYY: \nplayer->former_block_touched.x = %f\n", player->former_block_touched.x);
		// printf("player->block_touched.x = %f\n", player->block_touched.x);
		// printf("player->horizontal_wall_size_in_px = %f\n", player->horizontal_wall_size_in_px);
	}
	player->former_block_touched = player->block_touched;
}

//we are still drawing column by column
//firstly we need to know the complete column(y) length of our wall
//then we need to scale it in function of the texture size

void	draw_wall(t_vars *vars, int *x, int *y)
{
	if (ray_facing_up(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_texture(vars, *x, y, vars->south_tex);
	else if (ray_facing_up(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_texture(vars, *x, y, vars->north_tex);
	else if (ray_facing_right(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == false)
		draw_texture(vars, *x, y, vars->west_tex);
	else if (ray_facing_right(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == false)
		draw_texture(vars, *x, y, vars->east_tex);
}
