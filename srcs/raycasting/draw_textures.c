/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/11 19:44:28 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_orange_wall(t_vars *vars, int x, int y, t_texture tex)
{
	int	color;
	
	color = ORANGE;
	(void)tex;
	my_mlx_pixel_put(*vars, x, y, color);
	if (y == vars->game->player->proj_plan.wall_top_pos_y_in_px)
	{
		my_mlx_pixel_put(*vars, x, y, WHITE);
		printf("y = %i\n", y);
	}
}

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
	if (rounded_down(player->block_touched.x) == rounded_down(player->former_block_touched.x)
		&& rounded_down(player->block_touched.y) == rounded_down(player->former_block_touched.y))
		my_mlx_pixel_put(*vars, x, *y, color);
	else
	{
		player->proj_plan.wall_upper_left_x_in_px = player->former_block_touched.x;
		player->proj_plan.wall_upper_right_x_in_px = player->block_touched.x;
		// if (rounded_down(player->block_touched.x) != rounded_down(player->former_block_touched.x))
		// 	printf("player->block_touched.x = %f\n && player->former_block_touched.x = %f\n\n", rounded_down(player->block_touched.x), rounded_down(player->former_block_touched.x));
		// else
		// 	printf("player->block_touched.y = %f\n && player->former_block_touched.y = %f\n\n", rounded_down(player->block_touched.y), rounded_down(player->former_block_touched.y));
		color = WHITE;
		while (*y <= player->proj_plan.wall_lower_pos_y_in_px)
			my_mlx_pixel_put(*vars, x, (*y)++, color);
	}
	player->former_block_touched = player->block_touched;
}

//we are still drawing column by column
//firstly we need to know the complete column(y) length of our wall
//then we need to scale it in function of the texture size
/*void	draw_scaled_texture(t_vars *vars, int x, int *y, t_texture tex)
{
	t_player	*player;
	double		offset_y;
	int			color;

	player = vars->game->player;
	offset_y = *y + player->wall_height_in_px / (double)tex.height;
	while (*y < offset_y)
	{
		my_mlx_pixel_put(*vars, x, *y, color);
		(*y)++;
	}
	// printf("after loop: = %i\n", *y);
	// if (tex_x > 100000)
	// 	exit(0);
	// if (tex_x == 64)
	// {
	// 	tex_x = 0;
	// 	if (tex_y == 64)
	// 		tex_y = 0;
	// 	else
	// 		tex_y++;
	// }
	// else
	// 	tex_x++;
}*/

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