/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:13:24 by ml                #+#    #+#             */
/*   Updated: 2024/02/15 02:26:10 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_vars	*va;

	va = (t_vars *) param;
	if (va == NULL || va->mlx == NULL || va->maps == NULL
		|| keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit_app(va, 0, -1);
	else if (keydata.key == MLX_KEY_W)
		player_move(va, MLX_KEY_UP);
	else if (keydata.key == MLX_KEY_S)
		player_move(va, MLX_KEY_DOWN);
	else if (keydata.key == MLX_KEY_A)
		player_move(va, MLX_KEY_LEFT);
	else if (keydata.key == MLX_KEY_D)
		player_move(va, MLX_KEY_RIGHT);
}

int	main(int argc, char **argv)
{
	t_vars			vars;
	t_maploader		map;

	init_vars(&vars, &map);
	if (argc != 2)
		return (exit_app(&vars, 1, -1));
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".ber", 4) != 0)
		return (exit_app(&vars, 1, -1));
	if (load_map(&vars, &map, argv[1]) != 0)
		return (exit_app(&vars, 1, -1));
	vars.mlx = mlx_init(vars.max_x * TILE_SIZE, vars.max_y * TILE_SIZE,
			"so_long", false);
	if (init_tile(&vars) != 0)
		return (exit_app(&vars, 1, -1));
	draw_map(&vars, 0, 0);
	mlx_key_hook(vars.mlx, ft_hook, &vars);
	mlx_close_hook(vars.mlx, close_hook, &vars);
	mlx_loop(vars.mlx);
	return (exit_app(&vars, 0, -1));
}
