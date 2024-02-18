/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:13:33 by ml                #+#    #+#             */
/*   Updated: 2024/02/18 22:31:17 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stddef.h>

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
	vars->player.x = 0;
	vars->player.y = 0;
	vars->tile[WALL] = NULL;
	vars->tile[EMPTY] = NULL;
	vars->tile[PLAYER] = NULL;
	vars->tile[EXIT] = NULL;
	vars->tile[COLLECTIBLE] = NULL;
	vars->mlx = NULL;
	vars->maps = NULL;
	map->i = 0;
	map->exit_c = 0;
	map->player_c = 0;
}

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (size == 0 && ptr)
	{
		free(ptr);
		ptr = NULL;
		return (ptr);
	}
	new = (char *) ft_calloc(size, sizeof(char));
	if (new == NULL)
		return (NULL);
	if (ptr != NULL)
		ft_memcpy(new, ptr, size);
	free(ptr);
	ptr = new;
	return (ptr);
}

unsigned char	free_map(t_vars *vars, int fd)
{
	size_t	i;

	i = 0;
	while (i < vars->max_y)
	{
		if (vars->maps[i] != NULL)
			free(vars->maps[i]);
		vars->maps[i] = NULL;
		i++;
	}
	free(vars->maps);
	vars->maps = NULL;
	if (fd != -1)
		close(fd);
	return (1);
}
