#include "cub3d.h"

void    draw_minimap_pixels(t_vars vars, t_game *game, int map_x, int map_y)
{
    int block_size_x;
    int block_size_y;
    int pixel_x_start;
    int pixel_y_start;

    block_size_x = MINIMAP_LENGTH / game->n_cols;
    block_size_y = MINIMAP_HEIGHT / game->n_rows;
    pixel_x_start = MINIMAP_START_X + map_x * block_size_x;
    pixel_y_start = MINIMAP_START_Y + map_y * block_size_y;
    while (--block_size_y >= 0)
    {
        while (--block_size_x >= 0)
        {
            if ((int)game->player->pos_x / 64 == map_x && (int)game->player->pos_y / 64 == map_y)
                my_mlx_pixel_put(vars, pixel_x_start + block_size_x, pixel_y_start + block_size_y, YELLOW);
            else if (game->map[map_y][map_x] == '0' || game->map[map_y][map_x] == 'V')
                my_mlx_pixel_put(vars, pixel_x_start + block_size_x, pixel_y_start + block_size_y, BLUE);
            else if (game->map[map_y][map_x] == '1')
                my_mlx_pixel_put(vars, pixel_x_start + block_size_x, pixel_y_start + block_size_y, GREY);
        }
        block_size_x = MINIMAP_LENGTH / game->n_cols;
    }
}

void    draw_minimap(t_vars vars, t_game *game)
{
    int map_x;
    int map_y;

    map_y = -1;
    while (++map_y < game->n_rows)
    {
        map_x = -1;
        while (++map_x < game->n_cols)
            draw_minimap_pixels(vars, game, map_x, map_y);
    }
    mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.data.img, 0, 0);
}