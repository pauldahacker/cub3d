/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simon <simon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:15:43 by simarcha          #+#    #+#             */
/*   Updated: 2024/11/05 14:16:24 by simon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_texture(t_vars *vars, int x, int y, char *tex_path)
{
	int			tex_x;
	int			tex_y;
	t_texture	tex;
	void		*img;
	unsigned char	*data;
	unsigned int	color;

	tex_x = x % 64;
    tex_y = y % 64;
    img = mlx_xpm_file_to_image(vars->mlx_ptr, tex_path, &tex.width, &tex.height);
    if (!img)
        return; // Handle the case if image loading fails
    data = (unsigned char *)mlx_get_data_addr(img, &tex.bpp, &tex.size_line, &tex.endian);
    int pixel_offset = tex_y * tex.size_line + tex_x * (tex.bpp / 8);
	//printf("r: %d\ng: %d\nb: %d\n", (unsigned int)data[pixel_offset], (unsigned int)data[pixel_offset+1],(unsigned int)data[pixel_offset+2]);
	color = (data[pixel_offset]) << 16 
		| (data[pixel_offset + 1]) << 8
			| (data[pixel_offset + 2]);
	//printf("color: %d\n", color);
    my_mlx_pixel_put(*vars, x, y, color);
    //mlx_destroy_image(vars->mlx_ptr, img);
}

void	draw_wall(t_vars *vars, int *x, int *y)
{
	//double	texture_x;
	//double	texture_y;

	//texture_x = *x % 64;
	//texture_y = *y % 64;
	if (ray_facing_up(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_texture(vars, *x, *y, vars->game->south_path);
	//	my_mlx_pixel_put(*vars, *x, *y, STANDARD_GREY);//FACE SUD
	else if (ray_facing_up(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == true)
		draw_texture(vars, *x, *y, vars->game->north_path);
	//	my_mlx_pixel_put(*vars, *x, *y, BROWN);//FACE NORD
	else if (ray_facing_right(vars->game->player->ray_angle) == 1
		&& vars->game->player->horizontal_distance_chosen == false)
		draw_texture(vars, *x, *y, vars->game->west_path);
	//	my_mlx_pixel_put(*vars, *x, *y, WHITE);//FACE OUEST
	else if (ray_facing_right(vars->game->player->ray_angle) == 0
		&& vars->game->player->horizontal_distance_chosen == false)
		draw_texture(vars, *x, *y, vars->game->east_path);
	//	my_mlx_pixel_put(*vars, *x, *y, SILVER_GREY);//FACE EST
}

// void	draw_ceiling(t_vars *vars, int *x, int *y)
// {
	
// }

// void	draw_floor(t_vars *vars, int *x, int *y)
// {
	
// }