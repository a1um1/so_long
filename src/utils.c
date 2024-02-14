/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:13:33 by ml                #+#    #+#             */
/*   Updated: 2024/02/15 01:40:29 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_app(t_vars *vars, int exit_code, int fd)
{
	if (exit_code != 0 && vars != NULL)
		ft_printf("Error\n");
	if (vars == NULL)
	{
		ft_printf("Error\n");
		exit(exit_code);
		return (exit_code);
	}
	if (vars->maps != NULL)
		free_map(vars, fd);
	if (vars->mlx != NULL)
		mlx_close_window(vars->mlx);
	if (vars->tile[WALL] != NULL)
		mlx_delete_image(vars->mlx, vars->tile[WALL]);
	if (vars->tile[EMPTY] != NULL)
		mlx_delete_image(vars->mlx, vars->tile[EMPTY]);
	if (vars->tile[PLAYER] != NULL)
		mlx_delete_image(vars->mlx, vars->tile[PLAYER]);
	if (vars->tile[EXIT] != NULL)
		mlx_delete_image(vars->mlx, vars->tile[EXIT]);
	if (vars->tile[COLLECTIBLE] != NULL)
		mlx_delete_image(vars->mlx, vars->tile[COLLECTIBLE]);
	mlx_close_window(vars->mlx);
	exit(exit_code);
	return (exit_code);
}

void	close_hook(void *vars)
{
	exit_app(vars, 0, -1);
}

void	init_vars(t_vars *vars, t_maploader	*map)
{
	vars->max_x = 0;
	vars->max_y = 0;
	vars->max_collectible = 0;
	vars->collectible = 0;
	vars->moves = 0;
	vars->chac_pos[0] = 0;
	vars->chac_pos[1] = 0;
	map->player_c = 0;
	map->exit_c = 0;
	vars->tile[WALL] = NULL;
	vars->tile[EMPTY] = NULL;
	vars->tile[PLAYER] = NULL;
	vars->tile[EXIT] = NULL;
	vars->tile[COLLECTIBLE] = NULL;
	map->i = 0;
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	new = malloc(size * sizeof(int *));
	if (new == NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr != NULL)
	{
		ft_memcpy(new, ptr, size);
		free(ptr);
	}
	return (new);
}

unsigned char	free_map(t_vars *vars, int fd)
{
	unsigned int	i;

	i = 0;
	while (i < vars->max_y)
	{
		free(vars->maps[i]);
		vars->maps[i++] = NULL;
	}
	free(vars->maps);
	if (fd != -1)
		close(fd);
	vars->maps = NULL;
	return (1);
}
