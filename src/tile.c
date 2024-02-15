/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:13:52 by ml                #+#    #+#             */
/*   Updated: 2024/02/15 01:46:22 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tileat(t_vars *vars, t_tile tile, unsigned int x, unsigned int y)
{
	if (vars == NULL)
		return ;
	if (mlx_image_to_window(vars->mlx,
			vars->tile[tile], x * vars->tile[tile]->width,
			y * vars->tile[tile]->height) == -1)
		exit_app(vars, 1, -1);
}

unsigned int	load_tile(t_vars *vars, t_tile tile, const char *path)
{
	xpm_t	*texture;

	if (vars == NULL)
		return (exit_app(vars, 1, -1));
	texture = mlx_load_xpm42(path);
	if (texture == NULL)
		return (exit_app(vars, 1, -1));
	vars->tile[tile] = mlx_texture_to_image(vars->mlx, &texture->texture);
	mlx_delete_xpm42(texture);
	if (vars->tile[tile] == NULL)
		return (exit_app(vars, 1, -1));
	return (0);
}

unsigned int	check_tile_loaded(t_vars *vars)
{
	if (vars->tile[WALL] == NULL
		&& vars->tile[WALL]->count != TILE_SIZE * TILE_SIZE)
		return (1);
	if (vars->tile[EMPTY] == NULL
		&& vars->tile[EMPTY]->count != TILE_SIZE * TILE_SIZE)
		return (1);
	if (vars->tile[PLAYER] == NULL
		&& vars->tile[PLAYER]->count != TILE_SIZE * TILE_SIZE)
		return (1);
	if (vars->tile[EXIT] == NULL
		&& vars->tile[EXIT]->count != TILE_SIZE * TILE_SIZE)
		return (1);
	if (vars->tile[COLLECTIBLE] == NULL
		&& vars->tile[COLLECTIBLE]->count != TILE_SIZE * TILE_SIZE)
		return (1);
	return (0);
}

unsigned int	init_tile(t_vars *var)
{
	if (var == NULL || var->mlx == NULL)
		return (1);
	load_tile(var, WALL, TILE_WALL);
	load_tile(var, EMPTY, TILE_EMPTY);
	load_tile(var, PLAYER, TILE_PLAYER);
	load_tile(var, EXIT, TILE_EXIT);
	load_tile(var, COLLECTIBLE, TILE_COLLECTIBLE);
	return (check_tile_loaded(var));
}
