/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:25:17 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/27 19:23:59 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_grid
{
	double	x;
	double	y;
}	t_grid;

//if the ray is facing up

//we need thee function to know if the ray is facing up or down
//this function returns 1 if is going up, 0 if it's going down
int	ray_facing_up(t_ray *ray)
{
	if (ray->ray_from_player_y <= ray->pos_y)
		return (1);
	else
		return (0);
}

//We want to convert the position of our character (=player) that we have in 
//pixel into cubs unit.
//Given that the cubs unit are bigger than pixels, this returns an approximation

//This function gives us the coordinates of the character. But the return value
//is in pixel. In a second function, we will convert the pixel coordinates into
//grid/cubs unit.
t_grid	horizontal_coordinate_first_grid_point(t_ray *ray)
{
	t_grid	a;//first grid point called a

	if (ray_facing_up(ray) == 1)
		a.y = rounded_down(ray->pos_y / 64) * 64 - 1;
	else
		a.y = rounded_down(ray->pos_y / 64) * 64 + 64;
	a.x = ray->pos_x + (ray->pos_y - a.y) / tan(ray->angle);
	return (a);
}

double	find_horizontal_x_a(t_ray *ray)
{
	return ((double)64 / tan(ray->angle));
}

double	find_horizontal_y_a(t_ray *ray)
{
	if (ray_facing_up(ray) == 1)
		return ((double)-64);
	return ((double)64);
}

t_grid	horizontal_coordinate_next_grid_point(t_ray *ray, t_grid previous)
{
	t_grid	next;
	double	x_a;
	double	y_a;

	x_a = find_horizontal_x_a(ray);
	y_a = find_horizontal_y_a(ray);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	return (next);
}

t_grid	convert_pixel_to_grid(t_grid point)
{
	t_grid	result;

	result.x = point.x / 64;
	result.y = point.y / 64;
	return (result);
}

//Ensuite on a besoin d'une fonction/condition qui nous dit que s'il y a un mur
//au point en (convertit en grid) alors, on stop le process
//Sinon on continue jusqu'a le stopper

//This function find the first point, it means where the player is on the map
//then checks if there is a wall or not. If there is no, we will go on 
//until finding one to return the point where the wall is
t_grid	horizontal_point_crossing_wall(t_map **map, t_ray *ray)
{
	t_grid	current;
	t_grid	next;
	
	current = horizontal_coordinate_first_grid_point(ray);//in pixel
	current = convert_pixel_to_grid(current);//in grid/cub unit
	while ((map[(int)current.y][(int)current.x]) == 0)
	{
		next = horizontal_coordinate_next_grid_point(ray, current);
		next = convert_pixel_to_grid(next);
		current = next;
	}
	return (next);
}