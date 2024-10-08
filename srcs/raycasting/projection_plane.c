/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:00:06 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/07 11:37:12 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//How to calculate the distance from the wall ?
//tan formula in a triangle is: tan(angle) = opposite_side / adjacent_side
//                        <=>  adjacent_side = opposite_side / tan(angle)
//adjacent_side is our distance to the wall
//angle is our FOV angle which is 60° / 2 = 30°;
//Why divided by 2. Because we want to know the most straightforward ray, which
//is the one at the middle. Same for the opposite_side. The opposite_side is 
//our whole projection plane. But we use only half of it.
//Thus: opposite_side = PROJECTION_PLANE_X / 2 = 320 / 2 = 160
/*
            The most straightforward ray is the one at the middle.
            To calculate it we use trigonometry in a triangle.
                As if it should:
__________ = Projection Plane = __________
\        /                      \    |
 \      /                        \   |
  \    /                          \  |
   \  /                            \ |
    \/     = FOV: angle = 60°       \|
*/

//The uppermost left ray (first one) will draw the first row

void	init_ray_struct(t_ray *ray)
{
//    ray->pos_x = ;
//    ray->pos_y = ;
	ray->angle = 60;
	ray->distance_to_wall = (PROJECTION_PLANE_X / 2) / tan(ray->angle / 2);
	ray->angle_subsequent_ray = ray->angle / PROJECTION_PLANE_X;
}

//I want to convert the whole screen into a projection plane
//It means that instead of drawing pixel by pixel until WINDOWS_X/WINDOWS_Y
//I want to draw row by row. Because each row will be one angle from our FOV
//How to convert WINDOWS_X = 1600 into 320 rows


//pour tracer les rayons, on va devoir utiliser une boucle while qui commencera 
//de l'angle le + a gauche et qui finiera a droite.
//Sachant que notre FOV est de 60°, on prendra la position du joueur:
//S'il est place au nord   (N): l'angle du personnage sera entre 120° ≤ α ≤ 60°
//S'il est place a l'ouest (W): l'angle du personnage sera entre 210° ≤ α ≤ 150°
//S'il est place au sud    (S): l'angle du personnage sera entre 240° ≤ α ≤ 300°
//S'il est place a l'est   (E): l'angle du personnage sera entre 330° ≤ α ≤ 30° 
//car α % 360
//on commencera par dessiner l'angle de gauche (ie: 120) pour terminer a 
//l'angle de droite (ie 60)
//Comment tracer le trait jusqu'a ce que le mur ait ete atteint ?
