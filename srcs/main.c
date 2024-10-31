/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:24:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/10/31 18:29:27 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_vars vars, int x, int y, int color)
{
	char	*dst;

	dst = vars.data.addr + (y * vars.data.line_length + x
			* (vars.data.bpp / 8));
	if (*(unsigned int *)dst != (unsigned int)color)
		*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	int			img_width = BLOCK_SIZE;
	int			img_height = BLOCK_SIZE;

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
	printf("map has %i rows and %i columns\n", vars.game->n_rows, vars.game->n_cols);
	printf("player position map[%0.f][%0.f]\n", vars.game->player->pos_x, vars.game->player->pos_y);
	vars.game->player->pos_x = (vars.game->player->pos_x + 0.5) * BLOCK_SIZE;
	vars.game->player->pos_y = (vars.game->player->pos_y + 0.5) * BLOCK_SIZE;
	printf("angle_start = %f\n", vars.game->player->angle_start);
	printf("angle_end = %f\n", vars.game->player->angle_end);
	printf("subsequent_angle = %f\n", vars.game->player->subsequent_angle);
//	draw_every_ray(&vars);
//	draw_minimap(&vars, vars.game);
	vars.data.img = mlx_xpm_file_to_image(vars.mlx_ptr, "./textures/wall_1.xpm", &img_width, &img_height);
	mlx_hook(vars.win_ptr, 2, 1L << 0, &on_keypress, &vars);
	mlx_hook(vars.win_ptr, 17, 0, &on_destroy, &vars);
	mlx_loop(vars.mlx_ptr);
}
