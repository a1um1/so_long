/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:52:21 by ml                #+#    #+#             */
/*   Updated: 2024/02/12 01:02:27 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned char	is_valid_position(t_vars *vars, int x, int y)
{
	return (x >= 0 && y >= 0 && x < vars->max_x
		&& y < vars->max_y && vars->maps[y][x] != WALL);
}

void	flood_fill(t_vars *vars, t_map_check *check, int x, int y)
{
	if (!is_valid_position(vars, x, y))
		return ;
	if (check->visited[y][x])
		return ;
	check->visited[y][x] = 1;
	if (vars->maps[y][x] == EXIT) 
		(check->exit_found) = 1;
	else if (vars->maps[y][x] == COLLECTIBLE)
		(check->collectibles_found)++;
	flood_fill(vars, check, x - 1, y);
	flood_fill(vars, check, x + 1, y);
	flood_fill(vars, check, x, y - 1);
	flood_fill(vars, check, x, y + 1);
}

unsigned char	check_map_accessibility(t_vars *vars)
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
		{
			while (i > 0)
				free(check.visited[i--]);
			free(check.visited);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < vars->max_y)
	{
		ft_memset(check.visited[i], 0, vars->max_x);
		i++;
	}
	check.collectibles_found = 0;
	check.exit_found = 0;
	flood_fill(vars, &check, vars->chac_pos[0], vars->chac_pos[1]);
	return (check.exit_found && check.collectibles_found == vars->max_collectible);
}
