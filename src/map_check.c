/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:12:04 by tlakchai          #+#    #+#             */
/*   Updated: 2024/02/18 23:12:05 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

unsigned int	free_map_chk(t_map_check *chk, unsigned int max)
{
	unsigned int	i;

	i = 0;
	while (i < max)
	{
		free(chk->visited[i]);
		chk->visited[i++] = NULL;
	}
	free(chk->visited);
	chk->visited = NULL;
	return (0);
}

unsigned char	is_valid_position(t_vars *vars, unsigned int x, unsigned int y)
{
	return (x >= 0 && y >= 0 && x < vars->max_x
		&& y < vars->max_y && vars->maps[y][x] != WALL);
}

void	flood_fill(t_vars *vars, t_map_check *check, int x, int y)
{
	if (!is_valid_position(vars, x, y) || check->visited[y][x])
		return ;
	check->visited[y][x] = 1;
	if (vars->maps[y][x] == EXIT) 
		(check->exit_found) = 1;
	else if (vars->maps[y][x] == COLLECTIBLE)
		(check->collectible)++;
	if (check->exit_found && check->collectible == vars->max_collectible)
		return ;
	flood_fill(vars, check, x - 1, y);
	flood_fill(vars, check, x + 1, y);
	flood_fill(vars, check, x, y - 1);
	flood_fill(vars, check, x, y + 1);
}

unsigned char	map_check_accessibility(t_vars *vars)
{
	t_map_check		check;
	unsigned int	i;

	i = 0;
	check.visited = malloc(sizeof(unsigned char *) * vars->max_y);
	if (check.visited == NULL)
		return (0);
	while (i < vars->max_y)
	{
		check.visited[i] = malloc(sizeof(unsigned char) * vars->max_x);
		if (check.visited[i] == NULL)
			return (free_map_chk(&check, i));
		i++;
	}
	i = 0;
	while (i < vars->max_y)
		ft_memset(check.visited[i++], 0, vars->max_x);
	check.collectible = 0;
	check.exit_found = 0;
	flood_fill(vars, &check, vars->player.x, vars->player.y);
	free_map_chk(&check, vars->max_y);
	return (check.exit_found && check.collectible == vars->max_collectible);
}
