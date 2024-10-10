/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:22:16 by simarcha          #+#    #+#             */
/*   Updated: 2024/10/10 16:53:45 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

//I've coded the following functions thanks to this reference: 
//https://permadi.com/1996/05/ray-casting-tutorial-7/

//this function receives the player's coordinate. It returns the first vertical
//intersection between the player's ray and the following block
t_block	vertical_coordinate_first_block_point(t_player *player)
{
	t_block	a;

	if (ray_facing_right(player->angle) == 1)
		a.x = rounded_down(player->pos_x / BLOCK_SIZE) * BLOCK_SIZE + BLOCK_SIZE;
	else
		a.x = rounded_down(player->pos_x / BLOCK_SIZE) * BLOCK_SIZE - 1;

	check_vertical_angle_value(player);
//	printf("value before multiplication = %f\n", player->pos_y + (player->pos_x - a.x));
//	printf("multiplication = %f\n", tan(player->angle * (PI / 180)));
	a.y = player->pos_y + (player->pos_x - a.x) * tan(player->angle * (PI / 180));
	// printf("player->pos_x = %f\nplayer->pos_y = %f\nplayer->angle = %f\n\n", 
	// 		player->pos_x, player->pos_y, player->angle);
	// printf("a.x = %f\na.y = %f\n", a.x, a.y);
	return (a);
}

double	find_vertical_x_a(t_player *player)
{
	if (ray_facing_right(player->angle) == 1)
		return ((double)BLOCK_SIZE);
	return ((double)-BLOCK_SIZE);
}

//formula from the Pythagoras theorem to find the distance of the hypotenuse
//how to find the hypotenuse ? 
//We know the angle (player->ange) and the distance of one side of the triangle
//which is one cube (<=> BLOCK_SIZE unit)
double	find_vertical_y_a(t_player *player)
{
	return ((double)BLOCK_SIZE * tan(player->angle * (PI / 180)));
}

t_block	vertical_coordinate_next_block_point(t_player *player, t_block previous)
{
	t_block	next;
	double	x_a;
	double	y_a;

	x_a = find_vertical_x_a(player);
	y_a = find_vertical_y_a(player);
	next.x = previous.x + x_a;
	next.y = previous.y + y_a;
	return (next);
}

/*t_block	vertical_point_crossing_wall(t_vars *vars)
{
	t_block	current_in_block;
	t_block	current_in_px;
	t_block	next_in_block;
	t_block	next_in_px;
	int		i = 0;

	current_in_px = vertical_coordinate_first_block_point(vars->game->player);//in pixel
	current_in_block = convert_pixel_to_block(current_in_px);//in block/cub unit
	printf("current point y = %f && x = %f\n", current_in_px.y, current_in_px.x);
	printf("current point y = %f && x = %f\n", current_in_block.y, current_in_block.x);
	printf("\n\nin pixel x = %f\n", current_in_block.x);
	current_in_block.x = rounded_nearest_nb(current_in_block.x);
	printf("in block x = %f\n\n", current_in_block.x);
	current_in_block.y = rounded_nearest_nb(current_in_block.y);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
		return ((printf("final point y = %f && x = %f\n", current_in_px.y, current_in_px.x)), current_in_px);
	while (vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == '0'
			|| vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == 'V')
	{
		printf("i = %i\ncurrent point y = %f && x = %f: _%c_\n", i++, current_in_block.y, current_in_block.x, vars->game->map[(int)current_in_block.y][(int)current_in_block.x]);
		next_in_px = vertical_coordinate_next_block_point(vars->game->player, current_in_px);
		next_in_block = convert_pixel_to_block(next_in_px);
		next_in_block.x = rounded_nearest_nb(next_in_block.x);
		next_in_block.y = rounded_nearest_nb(next_in_block.y);
		if (check_coordinates_in_map(vars, next_in_block) == 0)
		{
			printf("final point y = %f && x = %f: _%c_\n", current_in_block.y, current_in_block.x, vars->game->map[(int)current_in_block.y][(int)current_in_block.x]);
			return (current_in_px);
		}
		current_in_px = next_in_px;
		current_in_block = next_in_block;
		printf("current point y = %f\n", current_in_block.y);
		printf("current point x = %f\n", current_in_block.x);
		printf("map[y][x] = %c\n", vars->game->map[(int)current_in_block.y][(int)current_in_block.x]);
	}
	printf("final point y = %f && x = %f: _%c_\n", current_in_px.y, current_in_px.x, vars->game->map[(int)current_in_px.y][(int)current_in_px.x]);
	return (current_in_px);
	//return (next_in_px);
}*/


t_block	vertical_point_crossing_wall(t_vars *vars)
{
	t_block	current_in_block;
	t_block	current_in_px;
	t_block	next_in_block;
	t_block	next_in_px;

	current_in_px = vertical_coordinate_first_block_point(vars->game->player);
	current_in_block = convert_pixel_to_block(current_in_px);
	current_in_block.x = rounded_nearest_nb(current_in_block.x);
	current_in_block.y = rounded_nearest_nb(current_in_block.y);
	if (check_coordinates_in_map(vars, current_in_block) == 0)
	{
		printf("vertical final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", current_in_px.y, current_in_px.x);
		printf("vertical final point in \033[1;34mblock\033[0m y = %f && x = %f\n", current_in_block.y, current_in_block.x);
		return (current_in_px);
	}
	while (vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == '0'
			|| vars->game->map[(int)current_in_block.y][(int)current_in_block.x] == 'V')
	{
		next_in_px = vertical_coordinate_next_block_point(vars->game->player, current_in_px);
		next_in_block = convert_pixel_to_block(next_in_px);
		next_in_block.x = rounded_nearest_nb(next_in_block.x);
		next_in_block.y = rounded_nearest_nb(next_in_block.y);
		if (check_coordinates_in_map(vars, next_in_block) == 0)
		{
			printf("vertical final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", current_in_px.y, current_in_px.x);
			printf("vertical final point in \033[1;34mblock\033[0m y = %f && x = %f\n", current_in_block.y, current_in_block.x);
			return (current_in_px);
		}
		current_in_px = next_in_px;
		current_in_block = next_in_block;
	}
	printf("vertical final point in \033[1;31mpixels\033[0m y = %f && x = %f\n", current_in_px.y, current_in_px.x);
	printf("vertical final point in \033[1;34mblock\033[0m y = %f && x = %f\n", current_in_block.y, current_in_block.x);
	return (current_in_px);
}
