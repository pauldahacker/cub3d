/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:56:54 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/23 16:32:06 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
DDA Algorithm to trace a line 
(used in dda)
*/
void	dda(t_vars vars, t_point *block, double dx, double dy)
{
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	i = 0;
	while (i < steps && block->x < (double)WINDOW_X
		&& block->y < (double)WINDOW_Y)
	{
        if (block->x < 0 || block->y < 0)
            return ;
		my_mlx_pixel_put(vars, (int)round(block->x),
			(int)round(block->y), SKY_BLUE);
		block->x += x_inc;
		block->y += y_inc;
		++i;
	}
}

/*
Traces a line with the help of DDA algorithm
(used in draw_minimap_fov)
*/
void	draw_line(t_vars vars, t_point *p1, t_point *p2)
{
	double	dx;
	double	dy;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	dda(vars, p1, dx, dy);
}

/*
draw_minimap_fov: Draws the FOV on the minimap.
It uses the same loop logic as draw_every_ray to draw the FOV in 2D.
That is, for each subsequent angle between angle_start and angle_end, it 
draws a line at that angle until it hits the closest wall in that direction.
To draw the line, it scales the result of return_intersection.
FYI: return_intersection returns a point representing the intersection with
a wall on the map. However, its coordinates are scaled BLOCK_SIZE times.
So for each subsequent angle, the result of return_intersection is scaled back
to the original map dimensions, then re-scaled to the minimap dimensions.
*/
void    draw_minimap_fov(t_vars *vars, t_game *game)
{
    t_point inter;
    t_point start;
    double  size_x;
    double  size_y;
    double  ray_angle;

    size_x = MINIMAP_LENGTH / game->n_cols;
    size_y = MINIMAP_HEIGHT / game->n_rows;
    ray_angle = game->player->angle_start;
    if (game->player->angle_end >= 300)
        game->player->angle_end -= 360;
    while (ray_angle > vars->game->player->angle_end)
    {
        start.x = MINIMAP_START_X + game->player->pos_x / BLOCK_SIZE * size_x;
        start.y = MINIMAP_START_Y + game->player->pos_y / BLOCK_SIZE * size_y;
        if (ray_angle <= 0)
            inter = return_intersection(vars, 360 + (int)rounded_down(ray_angle) % 360 + (ray_angle - rounded_down(ray_angle)));
        else
            inter = return_intersection(vars, ray_angle);
        if (inter.y < 0)
            inter.y = 0;
        inter.x = MINIMAP_START_X + (long)(inter.x / BLOCK_SIZE * size_x);
        inter.y = MINIMAP_START_Y + (long)(inter.y / BLOCK_SIZE * size_y);
        draw_line(*vars, &start, &inter);
        ray_angle -= game->player->subsequent_angle;
    }
    if (game->player->angle_end < 0)
        game->player->angle_end += 360;
}

/*
draw_minimap_tile: Draws a single tile in minimap.
It draws a size_x * size_y tile representing a floor or a wall
depending on the position in the map (i.e. map_x and map_y).
If it's a floor, draw a (sixe_x * size_y) BLUE tile.
If it's a wall, draw a (sixe_x * size_y) BROWN tile.
*/
void    draw_minimap_tile(t_vars vars, t_game *game, int map_x, int map_y)
{
    double size_x;
    double size_y;
    int start_x;
    int start_y;

    size_x = MINIMAP_LENGTH / game->n_cols;
    size_y = MINIMAP_HEIGHT / game->n_rows;
    start_x = MINIMAP_START_X + map_x * size_x;
    start_y = MINIMAP_START_Y + map_y * size_y;
    while (--size_y >= 0)
    {
        while (--size_x >= 0)
        {
            if (game->map[map_y][map_x] == '0' || game->map[map_y][map_x] == 'V')
                my_mlx_pixel_put(vars, start_x + size_x, start_y + size_y, BLUE);
            else if (game->map[map_y][map_x] == '1')
                my_mlx_pixel_put(vars, start_x + size_x, start_y + size_y, BROWN);
        }
        size_x = MINIMAP_LENGTH / game->n_cols;
    }
}

/*
draw_minimap_player: Draws the player on the minimap.
It draws a (size_x / 2) * (size_y / 2) YELLOW tile representing the player.
These dimensions are equal to 1/2 of a wall or floor tile. Decreasing its size
allows the player to move more freely in tight spaces.
Since player's starting position is set as the center of the starting tile,
We have to make the loop start at:
The scaled starting x minus a 1/4 of size_x (i.e. 1/2 of player width)
The scaled starting y minus a 1/4 of size_y (i.e. 1/2 of player height)
*/
void	draw_minimap_player(t_vars vars, t_game *game)
{
	double size_x;
    double size_y;
	int	start_x;
	int	start_y;

	size_x = MINIMAP_LENGTH / game->n_cols;
    size_y = MINIMAP_HEIGHT / game->n_rows;
	start_x = MINIMAP_START_X + game->player->pos_x / BLOCK_SIZE * size_x - size_x / 4;
	start_y = MINIMAP_START_Y +  game->player->pos_y / BLOCK_SIZE * size_y - size_y / 4;
    size_x /= 2;
    size_y /= 2;
	while (size_y > 0)
    {
        while (size_x > 0)
        {
			my_mlx_pixel_put(vars, start_x + size_x, start_y + size_y, YELLOW);
            --size_x;
        }
        size_x = MINIMAP_LENGTH / game->n_cols / 2;
        --size_y;
	}
}

/*
draw_minimap: draws the complete minimap.
Loops through the initial map, and uses draw_minimap_tile for each element
of the map to draw the map without the player or the FOV.
Adds the FOV using draw_minimap_fov.
Adds the player using draw_minimap_player.
*/
void    draw_minimap(t_vars *vars, t_game *game)
{
    int map_x;
    int map_y;

    map_y = -1;
    while (++map_y < game->n_rows)
    {
        map_x = -1;
        while (++map_x < game->n_cols)
            draw_minimap_tile(*vars, game, map_x, map_y);
    }
    draw_minimap_fov(vars, game);
	draw_minimap_player(*vars, game);
    mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
	vars->data.img = mlx_new_image(vars->mlx_ptr, WINDOW_X, WINDOW_Y);
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&(vars->data.bpp), &(vars->data.line_length),
			&(vars->data.endian));
}
