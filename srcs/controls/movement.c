#include "cub3d.h"

int	on_move_up(t_vars *vars, int attempted_speed)
{
	vars->game->player->pos_x += return_x_increment(vars, vars->game->player->angle, attempted_speed);
	vars->game->player->pos_y += return_y_increment(vars, vars->game->player->angle, attempted_speed);
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_left(t_vars *vars, int attempted_speed)
{
	vars->game->player->pos_x += return_x_increment(vars, vars->game->player->angle + 90, attempted_speed);
	vars->game->player->pos_y += return_y_increment(vars, vars->game->player->angle + 90, attempted_speed);
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_down(t_vars *vars, int attempted_speed)
{
	vars->game->player->pos_x += return_x_increment(vars, vars->game->player->angle + 180, attempted_speed);
	vars->game->player->pos_y += return_y_increment(vars, vars->game->player->angle + 180, attempted_speed);
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_right(t_vars *vars, int attempted_speed)
{
	vars->game->player->pos_x += return_x_increment(vars, vars->game->player->angle - 90, attempted_speed);
	vars->game->player->pos_y += return_y_increment(vars, vars->game->player->angle - 90, attempted_speed);
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}