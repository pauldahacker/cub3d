/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:24:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/23 17:19:28 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	//print_map_content(vars.game);
	printf("map has %i rows and %i columns\n", vars.game->n_rows, vars.game->n_cols);
	printf("player position map[%0.f][%0.f]\n", vars.game->player->pos_x, vars.game->player->pos_y);
	vars.game->player->pos_x *= BLOCK_SIZE;
	vars.game->player->pos_y *= BLOCK_SIZE;
	printf("angle_start = %f\n", vars.game->player->angle_start);
	printf("angle_end = %f\n", vars.game->player->angle_end);
	printf("subsequent_angle = %f\n", vars.game->player->subsequent_angle);
	draw_every_ray(&vars);
	printf("\n");
	//test_calculate_best_distance(&vars, vars.game->player->angle);
	//test_calculate_best_distance(&vars, 45.0);
	vars.game->player->pos_x += BLOCK_SIZE / 2;
	vars.game->player->pos_y += BLOCK_SIZE / 2;
	draw_minimap(&vars, vars.game);
	mlx_hook(vars.win_ptr, 2, 1L << 0, &on_keypress, &vars);
	mlx_hook(vars.win_ptr, 17, 0, &on_destroy, &vars);
	mlx_loop(vars.mlx_ptr);
}
