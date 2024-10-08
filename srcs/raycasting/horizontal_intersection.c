/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:25:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/08 17:22:42 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/ray-casting-tutorial-7/

//We want to convert the position of our character (=player) that we have in 
//pixel into cubs unit.
//Given that the cubs unit are bigger than pixels, this returns an approximation

//This function gives us the coordinates of the character into block/cubs unit.
static t_block	horizontal_coordinate_first_block_point(t_ray *ray)
{
	t_block	a;

	if (ray_facing_up(ray) == 1)
	{
		a.y = rounded_down(ray->pos_y / BLOCK_SIZE) * BLOCK_SIZE - 1;
	//	printf("ray is facing up\n");
	}
	else
		a.y = rounded_down(ray->pos_y / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	// printf("ray->pos_x = %f\nray->pos_y = %f\nray->angle = %f\n\n", 
	// 		ray->pos_x, ray->pos_y, ray->angle);
	a.x = ray->pos_x + (ray->pos_y - a.y) / tan(ray->angle);

//	printf("a.x = %f\na.y = %f\n", a.x, a.y);
	return (a);
}

static double	find_horizontal_x_a(t_ray *ray)
{
	return ((double)BLOCK_SIZE / tan(ray->angle));
}

static double	find_horizontal_y_a(t_ray *ray)
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
	// printf("\nin horizontal_coordinate_next_block_point\n");
	// printf("x_a = %f && y_a = %f\n", x_a, y_a);
	// printf("previous.x = %f && previous.y = %f\n", previous.x, previous.y);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
//	printf("\nin horizontal_coordinate_next_block_point\n");
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
		
	current_in_px = horizontal_coordinate_first_block_point(ray);//in pixel
	current_in_block = convert_pixel_to_block(current_in_px);//in block/cub unit
	current_in_block.x = rounded_nearest_nb(current_in_block.x);
	current_in_block.y = rounded_nearest_nb(current_in_block.y);
//	printf("current_in_block.x = %f\ncurrent_in_block.y = %f\n", current_in_block.x, current_in_block.y);
//	printf("map[(int)current_in_block.y][(int)current_in_block.x] = _%c_\n", map[(int)current_in_block.y][(int)current_in_block.x]);
	while (map[(int)current_in_block.y][(int)current_in_block.x] == 0 || map[(int)current_in_block.y][(int)current_in_block.x] == 'N')
	{
//		printf("entered in while loop\n");
		next_in_px = horizontal_coordinate_next_block_point(ray, current_in_px);
		printf("next_in_px.x = %f\nnext_in_px.y = %f\n", next_in_px.x, next_in_px.y);
		next_in_block = convert_pixel_to_block(next_in_px);
		printf("next_in_block.x = %f\nnext_in_block.y = %f\n", next_in_block.x, next_in_block.y);
		next_in_block.x = rounded_nearest_nb(next_in_block.x);
		next_in_block.y = rounded_nearest_nb(next_in_block.y);
		printf("converted in block next_in_block.x = %f\nnext_in_block.y = %f\n", next_in_block.x, next_in_block.y);
		current_in_px = next_in_px;
		current_in_block = next_in_block;
	}
	//printf("current line %i : %s\n", (int)current_in_block.y + 1, map[(int)current_in_block.y]);
	printf("current point x = %f && y = %f: %c\n", current_in_block.y, current_in_block.x, map[(int)current_in_block.y][(int)current_in_block.x]);
	return (next_in_px);
}

void	init_ray_for_test(t_ray *ray)
{
	ray->pos_x = 128;//the units have to be in pixels
	ray->pos_y = 704;
	ray->angle = 90;
}

//mon objectif pour le moment est de voir:
//a.x = 115
//a.y = 191
/*int	main(int argc, char **argv)
{
	t_ray	ray;
	char	**map;
	t_block	result;
	
	map = fd_into_array(argv[1]);
	init_ray_for_test(&ray);
	
	result = horizontal_point_crossing_wall(map, &ray);
	(void)result;
//	printf("result.x = %f\nresult.y = %f\n", result.x, result.y);

	(void)argc;
	return (0);
}*/