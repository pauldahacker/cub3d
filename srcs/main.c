/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:24:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/10 16:59:32 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_for_test(t_player *player)
{
	player->pos_x *= 64;//the units have to be in pixels
	player->pos_y *= 64;//
	player->angle = 0;
}

int	main(int argc, char **argv)
{
	t_vars		vars;

	vars.game = parse(argc, argv);
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
		return (EXIT_FAILURE);
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	if (!vars.win_ptr)
		return (free(vars.mlx_ptr), EXIT_FAILURE);
	vars.data.img = mlx_new_image(vars.mlx_ptr, WINDOW_X, WINDOW_Y);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &(vars.data.bpp),
			&(vars.data.line_length), &(vars.data.endian));
	
	draw_game(vars, vars.game);
	printf("position player in the map[%0.f][%0.f] = %c\n", \
	vars.game->player->pos_x, vars.game->player->pos_y, \
	vars.game->map[(int)vars.game->player->pos_x][(int)vars.game->player->pos_y]);
	printf("\n");
	init_player_for_test(vars.game->player);
	printf("map has %i rows and %i columns\n", vars.game->n_rows, vars.game->n_cols);
	vertical_point_crossing_wall(&vars);
	printf("\n");
	horizontal_point_crossing_wall(&vars);

	mlx_hook(vars.win_ptr, 2, 1L << 0, &on_keypress, &vars);
	mlx_hook(vars.win_ptr, 17, 0, &on_destroy, &vars);
	mlx_loop(vars.mlx_ptr);
}
