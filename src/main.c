#include "so_long.h"
#include <stdio.h>

void draw_tileat(t_vars *vars, t_tile tile, int x, int y)
{
	if (vars == NULL)
		return;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->tile[tile].img, x * vars->tile[tile].width, y * vars->tile[tile].height);
}

int exitApp(t_vars *vars)
{
	if (vars == NULL)
		return (0);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int movement(t_vars *vars, t_keycode keypress)
{
	int curX = vars->chac.x;
	int curY = vars->chac.y;
	if (vars == NULL)
		return (0);
	if (keypress == KEY_D)
	{
		if (vars->maps[vars->chac.y][vars->chac.x + 1] == WALL)
			return (0);
		vars->chac.x++;
	}
	if (keypress == KEY_A)
	{
		if (vars->maps[vars->chac.y][vars->chac.x - 1] == WALL)
			return (0);
		vars->chac.x--;
	}
	if (keypress == KEY_W)
	{
		if (vars->maps[vars->chac.y - 1][vars->chac.x] == WALL)
			return (0);
		vars->chac.y--;
	}
	if (keypress == KEY_S)
	{
		if (vars->maps[vars->chac.y + 1][vars->chac.x] == WALL)
			return (0);
		vars->chac.y++;
	}
	vars->moves++;
	draw_tileat(vars, EMPTY, curX, curY);
	if (vars->maps[vars->chac.y][vars->chac.x] == COLLECTIBLE)
	{
		vars->collectible++;
		vars->maps[vars->chac.y][vars->chac.x] = EMPTY;
		printf("COLLECTED %d/%d\n", vars->collectible, vars->max_collectible);
	}
	if (vars->maps[vars->chac.y][vars->chac.x] == EXIT && vars->collectible >= vars->max_collectible)
	{
		exitApp(vars);
	} else if (vars->maps[vars->chac.y][vars->chac.x] == EXIT)
		draw_tileat(vars, EXIT, vars->chac.x, vars->chac.y);
	if (vars->maps[curY][curX] == EXIT)
		draw_tileat(vars, EXIT, curX, curY);
	draw_tileat(vars, PLAYER, vars->chac.x, vars->chac.y);
	return 1;
}

int	keyhandle(int keycode, t_vars *vars)
{
	if (vars == NULL)
		return (0);
	if ((keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D))
		if (movement(vars, keycode))
			return (0);
	if (keycode == KEY_ESC)
		exitApp(vars);
	return (0);
}

void	draw_map(t_vars *vars)
{
	int x = 0;
	int y = 0;
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
			{
				vars->chac.x = x;
				vars->chac.y = y;
			}
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
	t_vars	vars;
	vars.max_x = 0;
	vars.max_y = 0;
	vars.max_collectible = 0;
	vars.collectible = 0;
	vars.moves = 0;
	if (load_map(&vars,argv[1]))
	{
		printf("Error\n");
		return (1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.max_x * TILE_SIZE, vars.max_y * TILE_SIZE, "so_long");
	vars.tile[EMPTY].img = mlx_xpm_file_to_image(vars.mlx, "assets/bg.xpm", &(vars.tile[EMPTY].width), &(vars.tile[EMPTY].height));
	vars.tile[WALL].img = mlx_xpm_file_to_image(vars.mlx, "assets/wall.xpm", &(vars.tile[WALL].width), &(vars.tile[WALL].height));
	vars.tile[PLAYER].img = mlx_xpm_file_to_image(vars.mlx, "assets/player.xpm", &(vars.tile[PLAYER].width), &(vars.tile[PLAYER].height));
	vars.tile[EXIT].img = mlx_xpm_file_to_image(vars.mlx, "assets/exit.xpm", &(vars.tile[EXIT].width), &(vars.tile[EXIT].height));
 	vars.tile[COLLECTIBLE].img = mlx_xpm_file_to_image(vars.mlx, "assets/collectable.xpm", &(vars.tile[COLLECTIBLE].width), &(vars.tile[COLLECTIBLE].height));
	draw_map(&vars);
	draw_tileat(&vars, PLAYER, vars.chac.x, vars.chac.y);
	mlx_hook(vars.win, 2, 1L<<0, keyhandle, &vars);
	mlx_hook(vars.win, 17, 0L, exitApp, &vars);
	mlx_loop(vars.mlx);
	return (0);
}