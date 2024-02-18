/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:14:33 by ml                #+#    #+#             */
/*   Updated: 2024/02/18 22:31:51 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	fill_map_line(t_vars *vars, char *line, char *player_c, char *exit_c)
{
	unsigned int	i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == '1')
			vars->maps[vars->max_y][i] = WALL;
		else if (line[i] == 'E' && map_add_exit(vars, exit_c, i))
			return (1);
		else if (line[i] == 'P' && map_add_player(vars, player_c, i))
			return (1);
		else if (line[i] == 'C')
		{
			vars->maps[vars->max_y][i] = COLLECTIBLE;
			vars->max_collectible++;
		}
		else if (line[i] == '0')
			vars->maps[vars->max_y][i] = EMPTY;
		i++;
	}
	return (0);
}

int	check_line(t_vars *vars, char *line, char *player_c, char *exit_c)
{
	unsigned int	i;

	i = 0;
	while (line[i] != 0 && line[i] != '\n')
		if (ft_strchr("01CEP", line[i++]) == NULL)
			return (1);
	if (vars->max_x != 0 && vars->max_x != i)
		return (1);
	vars->max_x = i;
	vars->maps[vars->max_y] = malloc(sizeof(int) * (i + 1));
	if (vars->maps[vars->max_y] == NULL)
		return (1);
	i = 0;
	if (fill_map_line(vars, line, player_c, exit_c))
		return (1);
	return (0);
}

int	check_map(t_vars *va, char player_c, char exit_c)
{
	if (va->max_collectible == 0 || va->max_y == 0 || !player_c || !exit_c)
		return (1);
	return (0);
}

char	load_map(t_vars *va, t_maploader *map, char *map_file)
{
	if (va == NULL || map_file == NULL)
		return (1);
	va->maps = ft_calloc(sizeof(int *), 1);
	if (va->maps == NULL)
		return (1);
	map->fd = open(map_file, O_RDONLY);
	map->line = get_next_line(map->fd);
	while (map->line != NULL)
	{
		if (check_line(va, map->line, &map->player_c, &map->exit_c) == 1)
			return (exit_app(va, 1, map->fd));
		free(map->line);
		va->maps = ft_realloc(va->maps, sizeof(int *) * (++va->max_y + 1));
		if (va->maps == NULL)
			return (exit_app(va, 1, map->fd));
		va->maps[va->max_y] = NULL;
		map->line = get_next_line(map->fd);
	}
	if (check_map(va, map->player_c, map->exit_c) == 1)
		return (exit_app(va, 1, map->fd));
	if (map_check_accessibility(va) == 0 || map_check_closed(va))
		return (exit_app(va, 1, map->fd));
	close(map->fd);
	return (0);
}
