/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:44:35 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/04 19:22:13 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_vars vars, int x, int y, int color)
{
	char	*dst;

	dst = vars.data.addr + (y * vars.data.line_length + x
			* (vars.data.bpp / 8));
	*(unsigned int *)dst = color;
}

//we have our windows which is 1600(WINDOW_X) by 900(WINDOW_Y)
//But the pixels that we draw are reflected on the projection/camera plan
//which is 320 by 200 (width * height)
//My goal is to draw the first projection plan row.
//We have to convert our window in a projection plan
//Then when we will have the first dimension, we will try to print our first row
//

//il est possile que tu aies besoin des coordonnes du joueurs au lieu des pixels x et y 
void	draw_game(t_vars vars, t_game *game)
{
	int	row_from_plan;
	int	x;
	int	y;
	
	row_from_plan = WINDOW_X / PROJECTION_PLANE_X;
	y = 0;
	while (y < WINDOW_Y)
	{
		x = 0;
		while (x < WINDOW_X)
		{
			if (x < row_from_plan)
				my_mlx_pixel_put(vars, x, y, GREY);
			else
				my_mlx_pixel_put(vars, x, y, WHITE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.data.img, 0, 0);
	(void)game;
}