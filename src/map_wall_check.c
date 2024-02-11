/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_wall_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 01:21:43 by ml                #+#    #+#             */
/*   Updated: 2024/02/12 01:35:26 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
