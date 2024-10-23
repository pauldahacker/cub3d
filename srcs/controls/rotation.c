#include "cub3d.h"

double  increment_angle(double angle, double to_add)
{
    double  res;

    res = angle + to_add;
    if (res > 360)
        return (res - 360);
    if (angle + to_add < 0)
        return (res + 360);
    return (res);
}

int	on_rotate_left(t_vars *vars, int attempted_speed)
{
    t_player    *player;

	if (!attempted_speed)
		return (0);
	player = vars->game->player;
	player->angle = increment_angle(player->angle, attempted_speed);
	player->angle_start = increment_angle(player->angle_start, attempted_speed);
	player->angle_end = increment_angle(player->angle_end, attempted_speed);
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
    return (0);
}

int	on_rotate_right(t_vars *vars, int attempted_speed)
{
    t_player    *player;

	if (!attempted_speed)
		return (0);
    player = vars->game->player;
    player->angle = increment_angle(player->angle, -attempted_speed);
    player->angle_start = increment_angle(player->angle_start, -attempted_speed);
	player->angle_end = increment_angle(player->angle_end, -attempted_speed);
    draw_every_ray(vars);
	draw_minimap(vars, vars->game);
    return (0);
}