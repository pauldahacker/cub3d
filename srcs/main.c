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

t_texture	init_texture(t_vars *vars, char *texture_path)
{
	t_texture	tex;

	tex.img = mlx_xpm_file_to_image(vars->mlx_ptr,
		texture_path, &tex.width, &tex.height);
	 if (!tex.img)
        handle_error(vars->game, "One of the textures failed to open\n");
	tex.data = (unsigned char *)mlx_get_data_addr(tex.img, 
		&tex.bpp, &tex.size_line, &tex.endian);
	return (tex);
}

void	init_all_textures(t_vars *vars)
{
	vars->north_tex = init_texture(vars, vars->game->north_path);
	vars->south_tex = init_texture(vars, vars->game->south_path);
	vars->west_tex = init_texture(vars, vars->game->west_path);
	vars->east_tex = init_texture(vars, vars->game->east_path);
}

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
	init_all_textures(&vars);
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
