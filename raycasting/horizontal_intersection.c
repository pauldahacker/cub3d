/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:25:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/30 18:50:46 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/ray-casting-tutorial-7/

//if the ray is facing up
//we need thee function to know if the ray is facing up or down
//this function returns 1 if is going up, 0 if it's going down
//how to know if the angle is facing up ?
//We start from the abscissa axis and we go anticlockwise.
//Basically, we know that angle is facing up if the angle goes from 
//0° ≤ angle < 180 (everything % 360)
int	ray_facing_up(t_ray *ray)
{
	if (ray->angle >= 0 && ray->angle < 180)
		return (1);
	else
		return (0);
}

//We want to convert the position of our character (=player) that we have in 
//pixel into cubs unit.
//Given that the cubs unit are bigger than pixels, this returns an approximation

//This function gives us the coordinates of the character. But the return value
//is in pixel. In a second function, we will convert the pixel coordinates into
//block/cubs unit.
t_block	horizontal_coordinate_first_block_point(t_ray *ray)
{
	t_block	a;

	if (ray_facing_up(ray) == 1)
	{
		a.y = rounded_down(ray->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
//		printf("entered in if\n");
	}
	else
	{
		a.y = rounded_down(ray->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
//		printf("entered in else\n");
	}
	printf("ray->pos_x = %f\nray->pos_y = %f\na.y        = %f\nray->angle = %f\n\n", 
			ray->pos_x, ray->pos_y, a.y, ray->angle);
	
	a.x = ray->pos_x + (ray->pos_y - a.y) / tan(ray->angle);

	printf("a.x = %f\na.y = %f\n", a.x, a.y);
	
	return (a);
}

double	find_horizontal_x_a(t_ray *ray)
{
	return ((double)BLOCK_SIZE / tan(ray->angle));
}

double	find_horizontal_y_a(t_ray *ray)
{
	if (ray_facing_up(ray) == 1)
		return ((double)-BLOCK_SIZE);
	return ((double)BLOCK_SIZE);
}

t_block	horizontal_coordinate_next_block_point(t_ray *ray, t_block previous)
{
	t_block	next;
	double	x_a;
	double	y_a;

	x_a = find_horizontal_x_a(ray);
	y_a = find_horizontal_y_a(ray);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	return (next);
}

t_block	convert_pixel_to_block(t_block point)
{
	t_block	result;

	result.x = point.x / BLOCK_SIZE;
	result.y = point.y / BLOCK_SIZE;
	//printf("result.x = %f\nresult.y = %f\n", result.x, result.y);
	return (result);
}

//Ensuite on a besoin d'une fonction/condition qui nous dit que s'il y a un mur
//au point en (convertit en block) alors, on stop le process
//Sinon on continue jusqu'a le stopper

//This function find the first point, it means where the player is on the map
//then checks if there is a wall or not. If there is no, we will go on 
//until finding one to return the point where the wall is
t_block	horizontal_point_crossing_wall(char **map, t_ray *ray)
{
	t_block	current;
	t_block	next;
	
	current = horizontal_coordinate_first_block_point(ray);//in pixel
	current = convert_pixel_to_block(current);//in block/cub unit
	while (map[(int)current.y][(int)current.x] == 0)
	{
		next = horizontal_coordinate_next_block_point(ray, current);
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

//mon objectif pour le moment est de voir:
//a.x = 115
//a.y = 191
int	main(int argc, char **argv)
{
	t_ray	ray;
	char	**map;
	t_block	result;
	
	map = fd_into_array(argv[1]);
	init_ray_for_test(&ray);
	
	result = horizontal_point_crossing_wall(map, &ray);
//	printf("result.x = %f\nresult.y = %f\n", result.x, result.y);

	(void)argc;
	return (0);
}*/