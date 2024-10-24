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

void	draw_line(t_vars vars, t_point *p1, t_point *p2)
{
	double	dx;
	double	dy;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	dda(vars, p1, dx, dy);
}

void    draw_minimap_fov(t_vars *vars, t_game *game)
{
    t_point inter;
    t_point start;
    int     size_x;
    int     size_y;
    double  ray_angle;

    size_x = MINIMAP_LENGTH / game->n_cols;
    size_y = MINIMAP_HEIGHT / game->n_rows;
    printf("Player coordinates:x: %f\ny: %f\n", vars->game->player->pos_x, vars->game->player->pos_y);
    ray_angle = game->player->angle_start;
    if (game->player->angle_end > 300)
        game->player->angle_end -= 360;
    while (ray_angle > vars->game->player->angle_end)
    {
        start.x = MINIMAP_START_X + game->player->pos_x / BLOCK_SIZE * size_x;
        start.y = MINIMAP_START_Y + game->player->pos_y / BLOCK_SIZE * size_y;
        if (ray_angle < 0)
            inter = return_intersection(vars, 360 + (int)rounded_down(ray_angle) % 360 + (ray_angle - rounded_down(ray_angle)));
        else
            inter = return_intersection(vars, ray_angle);
        if (inter.y < 0)
            inter.y = 0;
        inter.x = MINIMAP_START_X + inter.x / BLOCK_SIZE * size_x;
        inter.y = MINIMAP_START_Y + inter.y / BLOCK_SIZE * size_y;
        draw_line(*vars, &start, &inter);
        ray_angle -= game->player->subsequent_angle;
    }
    if (game->player->angle_end < 0)
        game->player->angle_end += 360;
}

void    draw_minimap_pixels(t_vars vars, t_game *game, int map_x, int map_y)
{
    int size_x;
    int size_y;
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

void	draw_minimap_player(t_vars vars, t_game *game)
{
	int size_x;
    int size_y;
	int	start_x;
	int	start_y;

	size_x = MINIMAP_LENGTH / game->n_cols;
    size_y = MINIMAP_HEIGHT / game->n_rows;
    printf("size_x: %d\nsize_y: %d\n", size_x, size_y);
	start_x = MINIMAP_START_X + game->player->pos_x / BLOCK_SIZE * size_x - size_x / 4;
	start_y = MINIMAP_START_Y + game->player->pos_y / BLOCK_SIZE * size_y - size_y / 4;
    size_x /= 2;
    size_y /= 2;
	while (size_y >= 0)
    {
        while (size_x >= 0)
        {
			my_mlx_pixel_put(vars, start_x + size_x, start_y + size_y, YELLOW);
            --size_x;
        }
        size_x = MINIMAP_LENGTH / game->n_cols / 2;
        --size_y;
	}
}

void    draw_minimap(t_vars *vars, t_game *game)
{
    int map_x;
    int map_y;

    map_y = -1;
    while (++map_y < game->n_rows)
    {
        map_x = -1;
        while (++map_x < game->n_cols)
            draw_minimap_pixels(*vars, game, map_x, map_y);
    }
    draw_minimap_fov(vars, game);
	draw_minimap_player(*vars, game);
    mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
	vars->data.img = mlx_new_image(vars->mlx_ptr, WINDOW_X, WINDOW_Y);
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&(vars->data.bpp), &(vars->data.line_length),
			&(vars->data.endian));
}
