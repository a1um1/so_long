/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 23:12:21 by tlakchai          #+#    #+#             */
/*   Updated: 2024/02/18 23:12:22 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

unsigned char	map_check_closed(t_vars *vars)
{
	unsigned int	i;
	unsigned int	j;

	if (vars->max_x < 3 || vars->max_y < 3)
		return (1);
	i = 0;
	while (i < vars->max_y)
	{
		if (vars->maps[i][0] != WALL || vars->maps[i][vars->max_x - 1] != WALL)
			return (1);
		i++;
	}
	j = 0;
	while (j < vars->max_x)
	{
		if (vars->maps[0][j] != WALL || vars->maps[vars->max_y - 1][j] != WALL)
			return (1);
		j++;
	}
	return (0);
}
