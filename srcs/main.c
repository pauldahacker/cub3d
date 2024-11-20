/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:24:48 by pde-masc          #+#    #+#             */
/*   Updated: 2024/11/20 12:48:55 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_vars *vars)
{
	vars->keys.w = 0;
	vars->keys.a = 0;
	vars->keys.s = 0;
	vars->keys.d = 0;
	vars->keys.left = 0;
	vars->keys.right = 0;
}

void	my_mlx_pixel_put(t_vars vars, int x, int y, int color)
{
	char	*dst;
	int		alpha;
	int		r;
	int		g;
	int		b;

	alpha = (color >> 24) & 0xFF;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	dst = vars.data.addr + (y * vars.data.line_length + x
			* (vars.data.bpp / 8));
	if (alpha > 0)
	{
		r = (r * alpha + ((*(unsigned int *)dst >> 16) & 0xFF) * (255 - alpha))
			/ 255;
		g = (g * alpha + ((*(unsigned int *)dst >> 8) & 0xFF) * (255 - alpha))
			/ 255;
		b = (b * alpha + (*(unsigned int *)dst & 0xFF) * (255 - alpha)) / 255;
		color = (r << 16) | (g << 8) | b;
	}
	*(unsigned int *)dst = color;
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
	t_vars	vars;

	vars.game = parse(argc, argv);
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
		return (EXIT_FAILURE);
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WINDOW_X, WINDOW_Y, "cub3d");
	if (!vars.win_ptr)
		return (free(vars.mlx_ptr), EXIT_FAILURE);
	init_all_textures(&vars);
	vars.game->player->pos_x = (vars.game->player->pos_x + 0.5) * BLOCK_SIZE;
	vars.game->player->pos_y = (vars.game->player->pos_y + 0.5) * BLOCK_SIZE;
	vars.data.img = mlx_new_image(vars.mlx_ptr, WINDOW_X, WINDOW_Y);
	vars.data.addr = mlx_get_data_addr(vars.data.img, &(vars.data.bpp),
			&(vars.data.line_length), &(vars.data.endian));
	init_keys(&vars);
	draw_every_ray(&vars);
	draw_minimap(&vars, vars.game);
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.data.img, 0, 0);
	mlx_hook(vars.win_ptr, X_EVENT_KEY_PRESS, 1L << 0, &on_keypress, &vars);
	mlx_hook(vars.win_ptr, X_EVENT_KEY_RELEASE, 1L << 1, &on_keyrelease, &vars);
	mlx_hook(vars.win_ptr, X_EVENT_DESTROY, 0, &on_destroy, &vars);
	mlx_loop_hook(vars.mlx_ptr, &update_player, &vars);
	mlx_loop(vars.mlx_ptr);
}
