/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:13:24 by ml                #+#    #+#             */
/*   Updated: 2024/02/12 00:31:43 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	keyhandle(int keycode, t_vars *vars)
{
	if (vars == NULL)
		return (0);
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
		if (player_move(vars, keycode,
				vars->chac_pos[0], vars->chac_pos[1]))
			return (0);
	if (keycode == KEY_ESC)
		exit_app(vars);
	return (0);
}

void	draw_map(t_vars *vars, unsigned int x, unsigned int y)
{
	while (y < vars->max_y)
	{
		x = 0;
		while (x < vars->max_x)
		{
			if (vars->maps[y][x] == WALL)
				draw_tileat(vars, WALL, x, y);
			else
				draw_tileat(vars, EMPTY, x, y);
			if (vars->maps[y][x] == PLAYER)
				draw_tileat(vars, PLAYER, x, y);
			else if (vars->maps[y][x] == EXIT)
				draw_tileat(vars, EXIT, x, y);
			else if (vars->maps[y][x] == COLLECTIBLE)
				draw_tileat(vars, COLLECTIBLE, x, y);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_maploader		map;

	init_vars(&vars, &map);
	if (argc != 2 || load_map(&vars, &map, argv[1]) != 0)
	{
		ft_printf("Error\n");
		return (1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.max_x * TILE_SIZE,
			vars.max_y * TILE_SIZE, "so_long");
	init_tile(&vars);
	draw_map(&vars, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, keyhandle, &vars);
	mlx_hook(vars.win, 17, 0L, exit_app, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
