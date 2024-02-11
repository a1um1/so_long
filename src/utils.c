/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:13:33 by ml                #+#    #+#             */
/*   Updated: 2024/02/12 02:01:12 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_app(t_vars *vars)
{
	if (vars == NULL)
		return (0);
	if (vars->maps != NULL)
		free_map(vars, -1);
	if (vars->mlx != NULL && vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
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
