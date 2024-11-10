/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/10 20:44:06 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_texture(t_vars *vars, int x, int y, t_texture tex)
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

//we are still drawing column by column
//firstly we need to know the complete column(y) length of our wall
//then we need to scale it in function of the texture size
void	draw_scaled_texture(t_vars *vars, int x, int *y, t_texture tex)
{

	t_player	*player;
	double		offset_y;
	int			color;
	// static int	tex_x = 0;

	player = vars->game->player;

	offset_y = *y + player->wall_height_in_px / (double)tex.height;
	// printf("player->wall_height_in_px = %f\n", player->wall_height_in_px);
	// printf("offset_y = %f\n", offset_y);
	// printf("before loop: y = %i\n", *y);
	color = array_colors[*y][x];
	//color = *(unsigned int *)vars->data.addr + (*y * tex.size_line + x * (tex.bpp / 8));
	// printf("color = %i\n", color);
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
}

void	draw_wall(t_vars *vars, int *x, int *y)
{
	if (ray_facing_up(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_scaled_texture(vars, *x, y, vars->south_tex);
		//draw_texture(vars, *x, *y, vars->south_tex);	
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