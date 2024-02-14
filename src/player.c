/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:17:02 by ml                #+#    #+#             */
/*   Updated: 2024/02/15 02:00:44 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_check(t_vars *vars, enum keys key, unsigned int x, unsigned int y)
{
	if (key == MLX_KEY_RIGHT && vars->maps[y][x + 1] != WALL)
		vars->player.x++;
	else if (key == MLX_KEY_LEFT && vars->maps[y][x - 1] != WALL)
		vars->player.x--;
	else if (key == MLX_KEY_UP && vars->maps[y - 1][x] != WALL)
		vars->player.y--;
	else if (key == MLX_KEY_DOWN && vars->maps[y + 1][x] != WALL)
		vars->player.y++;
	else
		return (1);
	return (0);
}

int	player_move(t_vars *vars, enum keys key)
{
	t_character	pos;

	if (vars == NULL)
		return (exit_app(vars, 1, -1));
	pos = vars->player;
	if (player_check(vars, key, pos.x, pos.y))
		return (0);
	vars->moves++;
	ft_printf("Moves: %d\n", vars->moves);
	draw_tileat(vars, EMPTY, pos.x, pos.y);
	if (vars->maps[vars->player.y][vars->player.x] == COLLECTIBLE)
	{
		vars->collectible++;
		vars->maps[vars->player.y][vars->player.x] = EMPTY;
	}
	if (vars->maps[vars->player.y][vars->player.x] == EXIT &&
		vars->collectible >= vars->max_collectible)
		exit_app(vars, 0, -1);
	else if (vars->maps[vars->player.y][vars->player.x] == EXIT)
		draw_tileat(vars, EXIT, vars->player.x, vars->player.y);
	if (vars->maps[vars->player.y][vars->player.x] == EXIT)
		draw_tileat(vars, EXIT, pos.x, pos.y);
	draw_tileat(vars, PLAYER, vars->player.x, vars->player.y);
	return (1);
}
