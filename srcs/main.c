/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:24:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/11 17:23:25 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_result_point(t_vars *vars)
{
	t_block	horizontal_pt_px;
	t_block	horizontal_pt_block;

	vars->game->player->angle = 0;
	horizontal_pt_px = horizontal_point_crossing_wall(vars);
	horizontal_pt_block = convert_pixel_to_block(horizontal_pt_px);
	if (horizontal_pt_px.reachable == 1)
	{
		printf("horizontal final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", horizontal_pt_px.y, horizontal_pt_px.x);
		printf("horizontal final point in \033[1;34mblock\033[0m y = %0.f && x = %0.f\n", horizontal_pt_block.y, horizontal_pt_block.x);
	}
	else
		printf("\033[1;29mhorizontal final point not reachable\033[0m\n");
	printf("\n");
	t_block	vertical_pt_px;
	t_block	vertical_pt_block;

	vertical_pt_px = vertical_point_crossing_wall(vars);
	vertical_pt_block = convert_pixel_to_block(vertical_pt_px);
	if (vertical_pt_px.reachable == 1)
	{
		printf("vertical final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", vertical_pt_px.y, vertical_pt_px.x);
		printf("vertical final point in \033[1;34mblock\033[0m y = %0.f && x = %0.f\n", vertical_pt_block.y, vertical_pt_block.x);
	}
	else
		printf("\033[1;29mvertical final point not reachable\033[0m\n");
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
	printf("position player in the map[%0.f][%0.f] = %c with angle = \n", \
	vars.game->player->pos_y, vars.game->player->pos_x, \
	vars.game->map[(int)vars.game->player->pos_y][(int)vars.game->player->pos_x]/*, \
	vars.game->player->angle*/);
	printf("map has %i rows and %i columns\n", vars.game->n_rows, vars.game->n_cols);
	printf("\n");
	vars.game->player->pos_x *= BLOCK_SIZE;
	vars.game->player->pos_y *= BLOCK_SIZE;
	print_result_point(&vars);

	mlx_hook(vars.win_ptr, 2, 1L << 0, &on_keypress, &vars);
	mlx_hook(vars.win_ptr, 17, 0, &on_destroy, &vars);
	mlx_loop(vars.mlx_ptr);
}
