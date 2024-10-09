/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:25:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/09 18:12:04 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/ray-casting-tutorial-7/

//We want to convert the position of our character (=player) that we have in 
//pixel into cubs unit.
//Given that the cubs unit are bigger than pixels, this returns an approximation

//This function gives us the coordinates of the character into block/cubs unit.
//tan receives an angle in radian but we work in degrees, so we add * (PI / 180)
//to convert it in radians
static t_block	horizontal_coordinate_first_block_point(t_ray *ray)
{
	t_block	a;

	if (ray_facing_up(ray->angle) == 1)
		a.y = rounded_down(ray->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
	else
		a.y = rounded_down(ray->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	
	check_horizontal_angle_value(ray);
	a.x = ray->pos_x + (ray->pos_y - a.y) / tan(ray->angle * (PI / 180));
	return (a);
}

static double	find_horizontal_x_a(t_ray *ray)
{
	return (rounded_down((double)BLOCK_SIZE / tan(ray->angle * PI / 180)));
}

static double	find_horizontal_y_a(t_ray *ray)
{
	if (ray_facing_up(ray->angle) == 1)
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
	// printf("\nin horizontal_coordinate_next_block_point\n");
	// printf("x_a = %f && y_a = %f\n", x_a, y_a);
	// printf("previous.x = %f && previous.y = %f\n", previous.x, previous.y);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	return (next);
}



//Ensuite on a besoin d'une fonction/condition qui nous dit que s'il y a un mur
//au point en (convertit en block) alors, on stop le process
//Sinon on continue jusqu'a le stopper

//This function find the first point, it means where the player is on the map
//then checks if there is a wall or not. If there is no, we will go on 
//until finding one to return the point where the wall is
t_block	horizontal_point_crossing_wall(char **map, t_ray *ray)
{
	t_block	current_in_block;
	t_block	current_in_px;
	t_block	next_in_block;
	t_block	next_in_px;
	int	i = 0;

	current_in_px = horizontal_coordinate_first_block_point(ray);//in pixel
	current_in_block = convert_pixel_to_block(current_in_px);//in block/cub unit
	printf("current point y = %f && x = %f\n", current_in_px.y, current_in_px.x);
	printf("current point y = %f && x = %f\n", current_in_block.y, current_in_block.x);
	current_in_block.x = rounded_nearest_nb(current_in_block.x);
	current_in_block.y = rounded_nearest_nb(current_in_block.y);
	while (map[(int)current_in_block.y][(int)current_in_block.x] == '0'
			|| map[(int)current_in_block.y][(int)current_in_block.x] == 'N')
	{
		printf("i = %i\ncurrent point y = %f && x = %f: _%c_\n", i++, current_in_block.y, current_in_block.x, map[(int)current_in_block.y][(int)current_in_block.x]);
		next_in_px = horizontal_coordinate_next_block_point(ray, current_in_px);
		next_in_block = convert_pixel_to_block(next_in_px);
		next_in_block.x = rounded_nearest_nb(next_in_block.x);
		next_in_block.y = rounded_nearest_nb(next_in_block.y);
		if (coordinates_in_map(map, next_in_block) == 0)
		{
			printf("final point y = %f && x = %f: _%c_\n", current_in_block.y, current_in_block.x, map[(int)current_in_block.y][(int)current_in_block.x]);
			return (current_in_px);
		}
		current_in_px = next_in_px;
		current_in_block = next_in_block;
	}
	printf("final point y = %f && x = %f: _%c_\n", current_in_block.y, current_in_block.x, map[(int)current_in_block.y][(int)current_in_block.x]);
	return (next_in_px);
}
//une fois que l'on a next_in_x, on peut calculer la distance en pixel parcourue

void	init_ray_for_test(t_ray *ray)
{
	ray->pos_x = 1 * 64;//the units have to be in pixels
	ray->pos_y = (8 * 64) + 10 * 64;//
	ray->angle = 90;
}

//we may need a function that checked if the point that we reached is out of bounds
