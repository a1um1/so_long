/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ml <ml@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:10:32 by ml                #+#    #+#             */
/*   Updated: 2024/02/12 01:57:18 by ml               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/mlx/mlx.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/ft_printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

# define TILE_SIZE			48
# define TILE_EMPTY			"assets/bg.xpm"
# define TILE_WALL			"assets/wall.xpm"
# define TILE_PLAYER		"assets/player.xpm"
# define TILE_EXIT			"assets/exit.xpm"
# define TILE_COLLECTIBLE	"assets/collectible.xpm"
# define MLX_LOAD_XPM		mlx_xpm_file_to_image

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_chatacter {
	int		x;
	int		y;
}	t_character;

typedef enum keycode {
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_ESC = 53
}	t_keycode;

typedef enum e_tile
{
	PLAYER,
	EXIT,
	EMPTY,
	WALL,
	COLLECTIBLE
}	t_tile;

typedef struct s_data
{
	void	*img;
	int		width;
	int		height;
}	t_data;

typedef struct s_vars {
	void			*mlx;
	void			*win;
	unsigned int	chac_pos[2];
	t_data			tile[5];
	t_tile			**maps;
	unsigned int	max_x;
	unsigned int	max_y;
	unsigned int	max_collectible;
	unsigned int	collectible;
	unsigned int	moves;
}				t_vars;

typedef struct s_maploader {
	char				*map;
	int					fd;
	unsigned int		i;
	char				*line;
	char				player_c;
	char				exit_c;
	char				count[2];
}	t_maploader;

typedef struct s_map_check {
	unsigned char	exit_found;
	unsigned int	collectible;
	unsigned char	**visited;
}	t_map_check;

/* MAP */
char			load_map(t_vars *va, t_maploader *map, char *map_file);
unsigned char	free_map(t_vars *vars, int fd);
unsigned char	map_add_player(t_vars *vars, char *player_c, unsigned int x);
unsigned char	map_add_exit(t_vars *vars, char *exit_c, unsigned int x);
unsigned char	map_check_accessibility(t_vars *vars);
unsigned char	map_check_closed(t_vars *vars);

/* TILE */
void			init_tile(t_vars *var);
void			draw_tileat(t_vars *vars, t_tile tile,
					unsigned int x, unsigned int y);

/* PLAYER */
int				player_move(t_vars *vars, t_keycode key,
					unsigned int x, unsigned int y);

/* UTILS */
int				exit_app(t_vars *vars);
void			init_vars(t_vars *vars, t_maploader	*map);
void			*ft_realloc(void *ptr, size_t size);

#endif