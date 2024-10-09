/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:22:16 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/30 19:09:56 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/ray-casting-tutorial-7/

//we need thee function to know if the ray is facing right or left
//this function returns 1 if is going right, 0 if it's going left
//how to know if the angle is facing right ?
//We start from the abscissa axis and we go anticlockwise.
//Basically, we know that angle is facing right if the angle goes from 
//-90° ≤ angle ≤ 90 (everything % 360)
int	ray_facing_right(t_ray *ray)
{
	if ((ray->angle >= 0 && ray->angle < 90)
		|| (ray->angle >= 270 && ray->angle < 360))
		return (1);
	else
		return (0);
}

t_block	vertical_coordinate_first_block_point(t_ray *ray)
{
	t_block	a;

	if (ray_facing_right(ray) == 1)
	{
		a.x = rounded_down(ray->pos_x / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
		printf("facing right\n");
	}
	else
		a.x = rounded_down(ray->pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;

	printf("ray->pos_x = %f\nray->pos_y = %f\na.y        = %f\nray->angle = %f\n\n", 
			ray->pos_x, ray->pos_y, a.y, ray->angle);

	a.y = ray->pos_y + (ray->pos_x - a.x) * tan(ray->angle);
	
	printf("a.x = %f\na.y = %f\n", a.x, a.y);

	return (a);
}

double	find_vertical_x_a(t_ray *ray)
{
	if (ray_facing_right(ray) == 1)
		return ((double)BLOCK_SIZE);
	return ((double)-BLOCK_SIZE);
}

//formula from the Pythagoras theorem to find the distance of the hypotenuse
//how to find the hypotenuse ? 
//We know the angle (ray->ange) and the distance of one side of the triangle
//which is one cube (<=> BLOCK_SIZE unit)
double	find_vertical_y_a(t_ray *ray)
{
	return ((double)BLOCK_SIZE * tan(ray->angle));
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
	t_block	current;
	t_block	next;

	current = vertical_coordinate_first_block_point(ray);//in pixel
	current = convert_pixel_to_block(current);//in block/cub unit
	printf("current.x = %f\ncurrent.y = %f\n", current.x, current.y);
	
	while ((map[(int)current.y][(int)current.x]) == 0)
	{
		next = vertical_coordinate_next_block_point(ray, current);
		next = convert_pixel_to_block(next);
		current = next;
	}
	return (next);
}

/*void	init_ray_for_test(t_ray *ray)
{
	ray->pos_x = 96;
	ray->pos_y = 224;
	ray->angle = 60;
}

int	main(int argc, char **argv)
{
	t_ray	ray;
	char	**map;
	t_block	result;
	
	map = fd_into_array(argv[1]);
	init_ray_for_test(&ray);
	
	result = vertical_point_crossing_wall(map, &ray);
	printf("result.x = %f\nresult.y = %f\n", result.x, result.y);

	(void)argc;
	return (0);
}*/
