/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:29:01 by simarcha          #+#    #+#             */
/*   Updated: 2024/09/25 16:47:16 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//pour dessiner les rayons tu dois calculer chaque deltas des distances 
//entre les x et les y jusqu'a trouver un mur
//ensuite tu dois utiliser la trigo pour que le mur ait une apparence plate et non courbee.


    // for(int x = 0; x < w; x++)
    // {
    //   //calculate ray position and direction
    //   double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
    //   double rayDirX = dirX + planeX * cameraX;
    //   double rayDirY = dirY + planeY * cameraX;

void	trying_to_draw_pixels(t_ray *ray)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	x = 0;
	while (x < WINDOW_X)
	{
		camera_x = 2 * x / (double)(WINDOW_X) - 1;//x coordinate in camera space
		x++;
	}

}

double	calculate_hypotenuse(t_ray *ray)
{
	double	pos_ray_x;//correspond a la coordonee en abscisse du rayon qui touce le mur
	double	pos_ray_y;

	pos_ray_x = (VARIABLE) - ray->pos_x;
	
}

    // Dimension of the Projection Plane = 320 x 200 units
    // Center of the Projection Plane = (160,100)
    // Distance to the Projection Plane = 277 units
    // Angle between subsequent rays = 60/320 degrees

//as long as we will use the function sqrt to calculate every rays, most of them
//will be in decimal. That's why we return a double type number
//Let's consider that our screen is divided in 320 columns (Projection Plane x).
//Our Field of Viev (FOV) is 60 degres.
//From the first ray drawn (ray[0]) to the second one, we will have to move the
//angle from 60/320 = 0.1875 degres
//this until reaching the 320th ray (ray[319])
double	calculate_every_rays(t_ray *ray)
{
	int	i;

	i = 0;
	while (i < PROJECTION_PLANE_X / 2)
	{
		
		i++;
	}
	while (i < PROJECTION_PLANE_X)
	{
		
		i++;
	}
}


	
