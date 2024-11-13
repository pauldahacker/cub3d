/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/13 19:06:00 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_texture(t_vars *vars, int x, int *y, t_texture tex)
{
	unsigned int	color;
	int				pixel_offset;
	double			top_y;
	double			low_y;
	double			tex_x;

	top_y = vars->game->player->proj_plan.wall_top_pos_y_in_px;
	low_y = vars->game->player->proj_plan.wall_lower_pos_y_in_px;
	if (fmod(round(vars->game->player->point_hit.x), BLOCK_SIZE) <= 0.000001)
	{
		tex_x = fmod(vars->game->player->point_hit.y, BLOCK_SIZE)
			/ BLOCK_SIZE * tex.width;
	}
	else
	{
		tex_x = fmod(vars->game->player->point_hit.x, BLOCK_SIZE)
			/ BLOCK_SIZE * tex.width;
	}
	pixel_offset = (int)((*y - top_y)
			/ (low_y - top_y) * tex.width) *tex.size_line
		+ (int)tex_x * (tex.bpp / 8);
	color = (tex.data[pixel_offset]) << 16 | (tex.data[pixel_offset + 1]) << 8
		| (tex.data[pixel_offset + 2]);
	my_mlx_pixel_put(*vars, x, *y, color);
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
