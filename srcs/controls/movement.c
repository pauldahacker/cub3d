#include "cub3d.h"

int	on_move_up(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed || attempted_speed > vars->game->player->pos_y)
		return (0);
	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y - attempted_speed;

	printf("player x: %d\nplayer y: %d\n", player_x, player_y);
	j = -1;
	while (++j < BLOCK_SIZE / 4)
	{
		i = -1;
		while (++i < BLOCK_SIZE / 4)
		{
			if (vars->game->map[(player_y - j) / BLOCK_SIZE][(player_x + i) / BLOCK_SIZE] == '1')
				return (on_move_up(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_y = vars->game->player->pos_y - attempted_speed;
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_left(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed || attempted_speed > vars->game->player->pos_x)
		return (0);
	player_x = (int)vars->game->player->pos_x - attempted_speed;
	player_y = (int)vars->game->player->pos_y;
	printf("player x: %d\nplayer y: %d\n", player_x, player_y);
	j = -1;
	while (++j < BLOCK_SIZE / 4)
	{
		i = -1;
		while (++i < BLOCK_SIZE / 4)
		{
			if (vars->game->map[(player_y + j) / BLOCK_SIZE][(player_x - i) / BLOCK_SIZE] == '1')
				return (on_move_left(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_x = vars->game->player->pos_x - attempted_speed;
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_down(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed || attempted_speed + vars->game->player->pos_y > WINDOW_Y)
		return (0);
	player_x = (int)vars->game->player->pos_x;
	player_y = (int)vars->game->player->pos_y + attempted_speed;
	printf("player x: %d\nplayer y: %d\n", player_x, player_y);
	j = -1;
	while (++j < BLOCK_SIZE / 4)
	{
		i = -1;
		while (++i < BLOCK_SIZE / 4)
		{
			if (vars->game->map[(player_y + j) / BLOCK_SIZE][(player_x + i) / BLOCK_SIZE] == '1')
				return (on_move_down(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_y = vars->game->player->pos_y + attempted_speed;
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}

int	on_move_right(t_vars *vars, int attempted_speed)
{
	int		player_x;
	int		player_y;
	int		i;
	int		j;

	if (!attempted_speed || attempted_speed + vars->game->player->pos_x > WINDOW_X)
		return (0);
	player_x = (int)vars->game->player->pos_x + attempted_speed;
	player_y = (int)vars->game->player->pos_y;
	printf("player x: %d\nplayer y: %d\n", player_x, player_y);
	j = -1;
	while (++j < BLOCK_SIZE / 4)
	{
		i = -1;
		while (++i < BLOCK_SIZE / 4)
		{
			if (vars->game->map[(player_y + j) / BLOCK_SIZE][(player_x + i) / BLOCK_SIZE] == '1')
				return (on_move_right(vars, attempted_speed - 1));
		}
	}
	vars->game->player->pos_x = vars->game->player->pos_x + attempted_speed;
	draw_every_ray(vars);
	draw_minimap(vars, vars->game);
	return (0);
}