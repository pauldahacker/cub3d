#include "cub3d.h"

double  return_x_increment(t_vars *vars, double angle, int attempted_speed)
{
    double		player_x;

    if (!attempted_speed)
        return (0);
    if (angle < 0)
        angle += 360;
    if (angle >= 360)
        angle -= 360;
    player_x = (vars->game->player->pos_x + cos(angle * PI / 180) * attempted_speed);
    if (vars->game->map[(int)(vars->game->player->pos_y / BLOCK_SIZE - 0.25)][(int)(player_x / BLOCK_SIZE - 0.25)] == '1'
			|| vars->game->map[(int)(vars->game->player->pos_y / BLOCK_SIZE + 0.25)][(int)(player_x / BLOCK_SIZE - 0.25)] == '1'
				|| vars->game->map[(int)(vars->game->player->pos_y / BLOCK_SIZE - 0.25)][(int)(player_x / BLOCK_SIZE + 0.25)] == '1'
					|| vars->game->map[(int)(vars->game->player->pos_y / BLOCK_SIZE + 0.25)][(int)(player_x / BLOCK_SIZE + 0.25)] == '1')
		return (return_x_increment(vars, angle, attempted_speed - 1));
    return (cos(angle * PI / 180) * attempted_speed);  
}

double  return_y_increment(t_vars *vars, double angle, int attempted_speed)
{
    double		player_y;

    if (!attempted_speed)
        return (0);
    player_y = (vars->game->player->pos_y - sin(angle * PI / 180) * attempted_speed);
    if (vars->game->map[(int)(player_y / BLOCK_SIZE - 0.25)][(int)(vars->game->player->pos_x / BLOCK_SIZE - 0.25)] == '1'
			|| vars->game->map[(int)(player_y / BLOCK_SIZE + 0.25)][(int)(vars->game->player->pos_x / BLOCK_SIZE - 0.25)] == '1'
				|| vars->game->map[(int)(player_y / BLOCK_SIZE - 0.25)][(int)(vars->game->player->pos_x / BLOCK_SIZE + 0.25)] == '1'
					|| vars->game->map[(int)(player_y / BLOCK_SIZE + 0.25)][(int)(vars->game->player->pos_x / BLOCK_SIZE + 0.25)] == '1')
		return (return_y_increment(vars, angle, attempted_speed - 1));
    return (-sin(angle * PI / 180) * attempted_speed);  
}