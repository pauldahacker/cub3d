#include "cub3d.h"

/*
DDA Algorithm to trace a line in any color.
*/
void	dda(t_vars vars, t_point *block, t_point d, int color)
{
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;

	if (fabs(d.x) > fabs(d.y))
		steps = fabs(d.x);
	else
		steps = fabs(d.y);
	x_inc = d.x / steps;
	y_inc = d.y / steps;
	i = 0;
	while (i < steps && block->x < (double)WINDOW_X
		&& block->y < (double)WINDOW_Y)
	{
		if (block->x < 0 || block->y < 0)
			return ;
		my_mlx_pixel_put(vars, (int)round(block->x),
			(int)round(block->y), color);
		block->x += x_inc;
		block->y += y_inc;
		++i;
	}
}

/*
Traces a line with the help of DDA algorithm
(used in draw_minimap_fov)
For the line to have a nice and visible color, we see if the minimap floor has been
colored in BLACK OR WHITE. If so, we draw the FOV in YELLOW.
Else, we draw the FOV in WHITE.
*/
void	draw_fov_line(t_vars vars, t_point *p1, t_point *p2)
{
	t_point	d;
	t_rgb rgb;

	rgb.r = linearize((vars.game->ceiling_color >> 16) & 0xFF);
    rgb.g = linearize((vars.game->ceiling_color >> 8) & 0xFF);
    rgb.b = linearize(vars.game->ceiling_color & 0xFF);
	d.x = p2->x - p1->x;
	d.y = p2->y - p1->y;
	if (return_contrasting(vars.game->ceiling_color) == BLACK
		|| return_contrasting(vars.game->ceiling_color) == WHITE)
		dda(vars, p1, d, add_shade(MINIMAP_SHADE, r_g_or_b(rgb)));
	else
		dda(vars, p1, d, add_shade(MINIMAP_SHADE, WHITE));
}