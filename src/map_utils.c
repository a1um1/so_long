/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:00:50 by ml                #+#    #+#             */
/*   Updated: 2024/02/15 01:55:15 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned char	map_add_player(t_vars *vars, char *player_c, unsigned int x)
{
	vars->maps[vars->max_y][x] = PLAYER;
	vars->player.x = x;
	vars->player.y = vars->max_y;
	if (*player_c)
		return (1);
	*player_c = 1;
	return (0);
}

unsigned char	map_add_exit(t_vars *vars, char *exit_c, unsigned int x)
{
	vars->maps[vars->max_y][x] = EXIT;
	if (*exit_c)
		return (1);
	*exit_c = 1;
	return (0);
}
