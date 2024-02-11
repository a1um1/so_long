/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:17:02 by ml                #+#    #+#             */
/*   Updated: 2024/02/12 00:29:38 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	player_check(t_vars *vars, t_keycode key, unsigned int x, unsigned int y)
{
	if (key == KEY_D && vars->maps[y][x + 1] != WALL)
		vars->chac_pos[0]++;
	else if (key == KEY_A && vars->maps[y][x - 1] != WALL)
		vars->chac_pos[0]--;
	else if (key == KEY_W && vars->maps[y - 1][x] != WALL)
		vars->chac_pos[1]--;
	else if (key == KEY_S && vars->maps[y + 1][x] != WALL)
		vars->chac_pos[1]++;
	else
		return (1);
	return (0);
}

int	player_move(t_vars *vars, t_keycode key, unsigned int x, unsigned int y)
{
	if (vars == NULL)
		return (0);
	if (player_check(vars, key, x, y))
		return (0);
	vars->moves++;
	ft_printf("Moves: %d\n", vars->moves);
	draw_tileat(vars, EMPTY, x, y);
	if (vars->maps[vars->chac_pos[1]][vars->chac_pos[0]] == COLLECTIBLE)
	{
		vars->collectible++;
		vars->maps[vars->chac_pos[1]][vars->chac_pos[0]] = EMPTY;
	}
	if (vars->maps[vars->chac_pos[1]][vars->chac_pos[0]] == EXIT &&
		vars->collectible >= vars->max_collectible)
		exit_app(vars);
	else if (vars->maps[vars->chac_pos[1]][vars->chac_pos[0]] == EXIT)
		draw_tileat(vars, EXIT, vars->chac_pos[0], vars->chac_pos[1]);
	if (vars->maps[y][x] == EXIT)
		draw_tileat(vars, EXIT, x, y);
	draw_tileat(vars, PLAYER, vars->chac_pos[0], vars->chac_pos[1]);
	return (1);
}
