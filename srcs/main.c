/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:24:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/09/24 17:54:18 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_vars		vars;
	//int			fd;

	check_args(argc, argv);
	//fd = open(argv[1], O_RDONLY);
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
		return (EXIT_FAILURE);
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	if (!vars.win_ptr)
		return (free(vars.mlx_ptr), EXIT_FAILURE);
	vars.data.img = mlx_new_image(vars.mlx_ptr, WINDOW_X, WINDOW_Y);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &(vars.data.bpp),
			&(vars.data.line_length), &(vars.data.endian));
	mlx_hook(vars.win_ptr, 2, 1L << 0, &on_keypress, &vars);
	mlx_hook(vars.win_ptr, 17, 0, &on_destroy, &vars);
	mlx_loop(vars.mlx_ptr);
}
