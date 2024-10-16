/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-masc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:56:54 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/16 13:56:56 by pde-masc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
                my_mlx_pixel_put(vars, start_x + size_x, start_y + size_y, GREY);
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
	start_x = MINIMAP_START_X + game->player->pos_x / BLOCK_SIZE * size_x;
	start_y = MINIMAP_START_Y +  game->player->pos_y / BLOCK_SIZE * size_y;
    size_x /= 2;
    size_y /= 2;
	while (--size_y >= 0)
    {
        while (--size_x >= 0)
			my_mlx_pixel_put(vars, start_x + size_x, start_y + size_y, YELLOW);
        size_x = MINIMAP_LENGTH / game->n_cols / 2;
	}
}

void    draw_minimap(t_vars *vars, t_game *game)
{
    int map_x;
    int map_y;

    map_y = -1;
	printf("minimap called\n");
    while (++map_y < game->n_rows)
    {
        map_x = -1;
        while (++map_x < game->n_cols)
            draw_minimap_pixels(*vars, game, map_x, map_y);
    }
	draw_minimap_player(*vars, game);
    mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->data.img, 0, 0);
	vars->data.img = mlx_new_image(vars->mlx_ptr, WINDOW_X, WINDOW_Y);
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&(vars->data.bpp), &(vars->data.line_length),
			&(vars->data.endian));
}
