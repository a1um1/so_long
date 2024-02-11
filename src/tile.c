/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:13:52 by ml                #+#    #+#             */
/*   Updated: 2024/02/11 22:22:37 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	draw_tileat(t_vars *vars, t_tile tile, unsigned int x, unsigned int y)
{
	if (vars == NULL)
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, 
		vars->tile[tile].img, x * vars->tile[tile].width, 
		y * vars->tile[tile].height);
}

void	init_tile(t_vars *var)
{
	var->tile[WALL].img = MLX_LOAD_XPM(var->mlx, TILE_WALL, 
			&var->tile[WALL].width, &var->tile[WALL].height);
	var->tile[EMPTY].img = MLX_LOAD_XPM(var->mlx, TILE_EMPTY, 
			&var->tile[EMPTY].width, &var->tile[EMPTY].height);
	var->tile[PLAYER].img = MLX_LOAD_XPM(var->mlx,
			TILE_PLAYER, &var->tile[PLAYER].width, 
			&var->tile[PLAYER].height);
	var->tile[EXIT].img = MLX_LOAD_XPM(var->mlx, TILE_EXIT, 
			&var->tile[EXIT].width, &var->tile[EXIT].height);
	var->tile[COLLECTIBLE].img = MLX_LOAD_XPM(var->mlx, 
			TILE_COLLECTIBLE, &var->tile[COLLECTIBLE].width,
			&var->tile[COLLECTIBLE].height);
}
