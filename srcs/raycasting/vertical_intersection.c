/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:22:16 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/28 13:06:40 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/ray-casting-tutorial-7/

//we need thee function to know if the ray is facing right or left
//this function returns 1 if is going right, 0 if it's going left
int	ray_facing_right(t_ray *ray)
{
	if (ray->ray_from_player_x >= ray->pos_x)
		return (1);
	else
		return (0);
}

t_grid	vertical_coordinate_first_grid_point(t_ray *ray)
{
	t_grid	a;//first grid point called a

	if (ray_facing_right(ray) == 1)
		a.x = rounded_down(ray->pos_x / 64) * 64 - 64;
	else
		a.x = rounded_down(ray->pos_x / 64) * 64 + -1;
	a.y = ray->pos_y + (ray->pos_x - a.x) / tan(ray->angle);
	return (a);
}

double	find_vertical_x_a(t_ray *ray)
{
	if (ray_facing_right(ray) == 1)
		return ((double)64);
	return ((double)-64);
}

//formula from the Pythagoras theorem to find the distance of the hypotenuse
//how to find the hypotenuse ? 
//We know the angle (ray->ange) and the distance of one side of the triangle
//which is one cube (<=> 64 unit)
double	find_vertical_y_a(t_ray *ray)
{
	return ((double)64 / tan(ray->angle));
}

t_grid	vertical_coordinate_next_grid_point(t_ray *ray, t_grid previous)
{
	t_grid	next;
	double	x_a;
	double	y_a;

	x_a = find_vertical_x_a(ray);
	y_a = find_vertical_y_a(ray);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	return (next);
}

t_grid	vertical_point_crossing_wall(t_grid **map, t_ray *ray)
{
	t_grid	current;
	t_grid	next;

	current = vertical_coordinate_first_grid_point(ray);//in pixel
	current = convert_pixel_to_grid(current);//in grid/cub unit
	while ((map[(int)current.y][(int)current.x]) == 0)
	{
		next = vertical_coordinate_next_grid_point(ray, current);
		next = convert_pixel_to_grid(next);
		current = next;
	}
	return (next);
}

t_ray	init_ray_for_test(t_ray ray)
{
	ray.pos_x = 10.5;
	ray.pos_y = 6.5;
	ray.ray_from_player_x = 14;
	ray.ray_from_player_y = 0;
	ray.angle = 90;
	return (ray);
}

int	main(void)
{
	// t_grid	a;
	t_ray	ray;
	
	// a.x = 96;
	// a.y = 224;
	ray = init_ray_for_test(ray);
	vertical_point_crossing_wall(map, &ray);
	return (0);
}