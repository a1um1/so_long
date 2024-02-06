#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

char load_map(t_vars *vars, char *map_file)
{
    if (vars == NULL || map_file == NULL)
        return 1;
    vars->maps = malloc(sizeof(int *) * 1);
    if (vars->maps == NULL)
        return 1;
    vars->maps[0] = NULL;
    int fd = open(map_file, O_RDONLY);
    char *line = get_next_line(fd);
    while (line != NULL)
    {
        int i = 0;
        while (line[i] != 0 && line[i] != '\n') {
            if (strchr("01CEP", line[i++]) == NULL)
                return 1;
        }
        if (vars->max_x != 0 && vars->max_x != i)
            return 1;
        vars->max_x = i;
        int *p = malloc(sizeof(int) * (i + 1));
        if (p == NULL)
            return 1;
        i = 0;
        while (line[i] != 0) {
            if (line[i] == '1')
                p[i] = WALL;
            else if (line[i] == 'E')
                p[i] = EXIT;
            else if (line[i] == 'P')
                p[i] = PLAYER;
            else if (line[i] == 'C')
            {
                p[i] = COLLECTIBLE;
                vars->max_collectible++;
            }
            else
                p[i] = EMPTY;
            i++;
        }
        free(line);
        vars->max_y++;
        vars->maps = realloc(vars->maps, sizeof(int *) * (vars->max_y + 1));
        if (vars->maps == NULL)
            return 1;
        vars->maps[vars->max_y - 1] = p;
        line = get_next_line(fd);
    }
    vars->maps[vars->max_y] = NULL;
    return 0;
}