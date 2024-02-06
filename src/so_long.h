#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/mlx/mlx.h"
# include "../lib/get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>


#define TILE_SIZE 48

typedef struct {
	unsigned char B, G, R, A;
}   RGB;

typedef union {
	RGB rgb;
		unsigned int value;
		unsigned int array[4];
}   Color;

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
} t_character;

typedef enum keycode {
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_ESC = 53
} t_keycode;

typedef enum e_tile {
    EMPTY,
    WALL,
    PLAYER,
    EXIT,
    COLLECTIBLE
} t_tile;

typedef struct	s_data {
	void	*img;
	int		width;
	int		height;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_character chac;
    t_data	tile[5];
	int		**maps;
	int		max_x;
	int		max_y;
	int		max_collectible;
	int		collectible;
	int		moves;
}				t_vars;

char load_map(t_vars *vars, char *map_file);

#endif