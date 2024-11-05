/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:24:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/05 13:49:07 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION

#include "cub3d.h"

#include "mlx.h"
#include "../miniaudio/miniaudio.h"

void	init_keys(t_vars *vars)
{
	vars->keys.w = 0;
	vars->keys.a = 0;
	vars->keys.s = 0;
	vars->keys.d = 0;
	vars->keys.left = 0;
	vars->keys.right = 0;
}
// connard
/*
int main() {
    void *mlx;
	void *win;
    t_texture *texture;
    int width, height;
	int bpp, size_line, endian;

    mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "Affichage d'une image XPM");
    texture = mlx_xpm_file_to_image(mlx, "./textures/wall_1.xpm", &width, &height);
	char *data = mlx_get_data_addr(texture, &bpp, &size_line, &endian);
	mlx_put_image_to_window(mlx,win,texture,0,0);
	printf("bpp: %d, size line: %d, endian: %d\n", bpp, size_line, endian);
    // Dans textures/wall_1.xpm, il y a le caractere '3' a la position 0,0.
	// Le '3' correspond normalement a la couleur #C7C7C7, donc avec:
	// R = C7 (hex) = 124, G = C7 (hex) = 124 et B = C7 (hex) = 124
	int i=-1;
	while (++i < 64)
		 printf("Color at (%d): %d\n", i, (unsigned int)data[i]);
    printf("Color at (0): %d\n", (unsigned int)data[0]);
	printf("Color at (1): %d\n", (unsigned int)data[1]);
	printf("Color at (2): %d\n", (unsigned int)data[2]);
	printf("Color at (3): %d\n", (unsigned int)data[3]);

	// Dans textures/wall_1.xpm, il y a le caractere '%' a la position 5,2.
	// Le '%' correspond normalement a la couleur #483818, donc avec:
	// R = 48 (hex) = 72, G = 38 (hex) = 56 et B = 18 (hex) = 24
	printf("Color at ((2 * size_line) + (5 * sizeof(int))): %d\n", (unsigned int)data[(2 * size_line) + (5 * sizeof(int))]);
	printf("Color at ((2 * size_line) + (5 * sizeof(int))) + 1: %d\n", (unsigned int)data[((2 * size_line) + (5 * sizeof(int))) + 1]);
	printf("Color at ((2 * size_line) + (5 * sizeof(int))) + 2: %d\n", (unsigned int)data[((2 * size_line) + (5 * sizeof(int))) + 2]);
	printf("Color at ((2 * size_line) + (5 * sizeof(int))) + 3: %d\n", (unsigned int)data[((2 * size_line) + (5 * sizeof(int))) + 3]);
	// Donc comme on peut voir sur le output:
	// apres avoir appele mlx_get_data_addr() sur texture, on peut recup les donnees du xpm:
	// elles sont stockees dans une liste (char *) et sont representees en RGBA.
	// pour retrouver ces valeurs RGBA, il suffit de cast le caractere a un (unsigned int).
	mlx_loop(mlx);
    mlx_destroy_image(mlx, texture);
    mlx_destroy_window(mlx, win); // Assuming you have created a window
    return 0;
}
*/

int	main(int argc, char **argv)
{
	t_vars		vars;
	ma_engine	engine;

	vars.game = parse(argc, argv);
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr || ma_engine_init(NULL, &engine) != MA_SUCCESS)
		return (EXIT_FAILURE);
	vars.engine = (void *)&engine;
    ma_engine_play_sound(&engine, "Polynomial_C.mp3", NULL);

	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	if (!vars.win_ptr)
		return (free(vars.mlx_ptr), EXIT_FAILURE);
	vars.data.img = mlx_new_image(vars.mlx_ptr, WINDOW_X, WINDOW_Y);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &(vars.data.bpp),
			&(vars.data.line_length), &(vars.data.endian));
	init_keys(&vars);
	//print_map_content(vars.game);
	printf("map has %i rows and %i columns\n", vars.game->n_rows, vars.game->n_cols);
	printf("player position map[%0.f][%0.f]\n", vars.game->player->pos_x, vars.game->player->pos_y);
	vars.game->player->pos_x = (vars.game->player->pos_x + 0.5) * BLOCK_SIZE;
	vars.game->player->pos_y = (vars.game->player->pos_y + 0.5) * BLOCK_SIZE;
	printf("angle_start = %f\n", vars.game->player->angle_start);
	printf("angle_end = %f\n", vars.game->player->angle_end);
	printf("subsequent_angle = %f\n", vars.game->player->subsequent_angle);
	draw_every_ray(&vars);
	draw_minimap(&vars, vars.game);
	mlx_hook(vars.win_ptr, X_EVENT_KEY_PRESS, 1L<<0, &on_keypress, &vars);
	mlx_hook(vars.win_ptr, X_EVENT_KEY_RELEASE, 1L<<1, &on_keyrelease, &vars);
	mlx_hook(vars.win_ptr, X_EVENT_DESTROY, 0, &on_destroy, &vars);
	mlx_loop_hook(vars.mlx_ptr, &update_player, &vars);
	mlx_loop(vars.mlx_ptr);
}
