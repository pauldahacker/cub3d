/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:22:16 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/09 14:47:13 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/ray-casting-tutorial-7/

t_block	vertical_coordinate_first_block_point(t_ray *ray)
{
	t_block	a;
	
	printf("ray->pos_x = %f\nray->pos_y = %f\nray->angle = %f\n\n", 
			ray->pos_x, ray->pos_y, ray->angle);
	if (ray_facing_right(ray->angle) == 1)
	{
		a.x = rounded_down(ray->pos_x / BLOCK_SIZE) * BLOCK_SIZE;// + BLOCK_SIZE;
		printf("facing right\n");
	}
	else
		a.x = rounded_down(ray->pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;

	//ce calcul de coordonne est eventuellement a reverifier
	a.y = ray->pos_y + (ray->pos_x - a.x) * tan(ray->angle * (PI / 180));
	printf("ray->pos_x = %f\nray->pos_y = %f\nray->angle = %f\n\n", 
			ray->pos_x, ray->pos_y, ray->angle);

	printf("a.x = %f\na.y = %f\n", a.x, a.y);
	return (a);
}

double	find_vertical_x_a(t_ray *ray)
{
	if (ray_facing_right(ray->angle) == 1)
		return ((double)BLOCK_SIZE);
	return ((double)-BLOCK_SIZE);
}

//formula from the Pythagoras theorem to find the distance of the hypotenuse
//how to find the hypotenuse ? 
//We know the angle (ray->ange) and the distance of one side of the triangle
//which is one cube (<=> BLOCK_SIZE unit)
double	find_vertical_y_a(t_ray *ray)
{
	return ((double)BLOCK_SIZE * tan(ray->angle * (PI / 180)));
}

t_block	vertical_coordinate_next_block_point(t_ray *ray, t_block previous)
{
	t_block	next;
	double	x_a;
	double	y_a;

	x_a = find_vertical_x_a(ray);
	y_a = find_vertical_y_a(ray);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	return (next);
}

t_block	vertical_point_crossing_wall(char **map, t_ray *ray)
{
	t_block	current_in_block;
	t_block	current_in_px;
	t_block	next_in_block;
	t_block	next_in_px;
	int		i = 0;

	current_in_px = vertical_coordinate_first_block_point(ray);//in pixel
	current_in_block = convert_pixel_to_block(current_in_px);//in block/cub unit
	printf("current point y = %f && x = %f\n", current_in_px.y, current_in_px.x);
	printf("current point y = %f && x = %f\n", current_in_block.y, current_in_block.x);
	current_in_block.x = rounded_nearest_nb(current_in_block.x);
	current_in_block.y = rounded_nearest_nb(current_in_block.y);
	while (map[(int)current_in_block.y][(int)current_in_block.x] == '0'
			|| map[(int)current_in_block.y][(int)current_in_block.x] == 'N')
	{
		printf("i = %i\ncurrent point y = %f && x = %f: _%c_\n", i++, current_in_block.y, current_in_block.x, map[(int)current_in_block.y][(int)current_in_block.x]);
		next_in_px = vertical_coordinate_next_block_point(ray, current_in_px);
		next_in_block = convert_pixel_to_block(next_in_px);
		next_in_block.x = rounded_nearest_nb(next_in_block.x);
		next_in_block.y = rounded_nearest_nb(next_in_block.y);
		current_in_px = next_in_px;
		current_in_block = next_in_block;
	}
	printf("final point y = %f && x = %f: _%c_\n", current_in_block.y, current_in_block.x, map[(int)current_in_block.y][(int)current_in_block.x]);
	return (next_in_px);
}

/*void	init_ray_for_test(t_ray *ray)
{
	ray->pos_x = 1 * 64;// = 160 the units have to be in pixels
	ray->pos_y = (8 * 64) + 10 * 64;// = 672
	ray->angle = PI / 4;
}*/

