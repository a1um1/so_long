#include "../lib/mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 18
#define HEIGHT 10
#define TILE_SIZE 32

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct {
	unsigned char B, G, R, A;
}RGB;
typedef union{
	RGB rgb;
		unsigned int value;
		unsigned int array[4];
}Color;

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
typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_character chac;
	int		**maps;
	int		max_x;
	int		max_y;
}				t_vars;

void draw_wall(t_vars *vars)
{
	if (vars == NULL)
		return;
	int tileX = 0;
	int tileY = 0;
	t_data	img2;
	char	*relative_path = "./wall2.xpm";
	int		img_width;
	int		img_height;
	img2.img = mlx_xpm_file_to_image(vars->mlx, relative_path, &img_width, &img_height);
	while (tileX < (vars->max_x * TILE_SIZE - 1)) {
		mlx_put_image_to_window(vars->mlx, vars->win, img2.img, tileX, 0);
		mlx_put_image_to_window(vars->mlx, vars->win, img2.img, tileX, (vars->max_y * TILE_SIZE)- img_height);
		tileX+=img_width;
	}

	while (tileY <( vars->max_y * TILE_SIZE - 1)) {
		mlx_put_image_to_window(vars->mlx, vars->win, img2.img, 0, tileY);
		mlx_put_image_to_window(vars->mlx, vars->win, img2.img, (vars->max_x * TILE_SIZE)-img_width, tileY);
		tileY+=img_height;
	}
}

void draw_background(t_vars *vars)
{
	if (vars == NULL)
		return;
	int tileX = 0;
	int tileY = 0;
	t_data	img2;
	char	*relative_path = "./bg2.xpm";
	int		img_width;
	int		img_height;
	img2.img = mlx_xpm_file_to_image(vars->mlx, relative_path, &img_width, &img_height);
	while (tileX < vars->max_x * TILE_SIZE) {
		tileY = 0;
		while (tileY < vars->max_y * TILE_SIZE) {
			mlx_put_image_to_window(vars->mlx, vars->win, img2.img, tileX, tileY);
			tileY+=img_height;
		}
		tileX+=img_width;
	}
}

void draw_Character(t_vars *vars)
{
	if (vars == NULL)
		return;
	t_data	img2;
	char	*relative_path = "./chac_1.xpm";
	int		img_width;
	int		img_height;
	img2.img = mlx_xpm_file_to_image(vars->mlx, relative_path, &img_width, &img_height);
	mlx_put_image_to_window(vars->mlx, vars->win, img2.img, vars->chac.x * TILE_SIZE, vars->chac.y * TILE_SIZE);

}

int exitApp(t_vars *vars)
{
	if (vars == NULL)
		return (0);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	keyhandle(int keycode, t_vars *vars)
{

	if (vars == NULL)
		return (0);
	if (keycode == 53)
		exitApp(vars);
	/* RIGHT */
	if (keycode == 124)
	{
		if (vars->chac.x == vars->max_x - 1)
			return (0);
		vars->chac.x++;
		draw_background(vars);
		draw_wall(vars);
		draw_Character(vars);
	}
	/* LEFT */
	if (keycode == 123)
	{
		if (vars->chac.x < 1)
			return (0);
		vars->chac.x--;
		draw_background(vars);
		draw_wall(vars);
		draw_Character(vars);
	}
	/* TOP */
	if (keycode == 126)
	{
		if (vars->chac.y < 1)
			return (0);
		vars->chac.y--;
		draw_background(vars);
		draw_wall(vars);
		draw_Character(vars);
	}
	/* DOWN */
	if (keycode == 125)
	{
		if (vars->chac.y ==  vars->max_y - 1)
			return (0);
		vars->chac.y++;
		draw_background(vars);
		draw_wall(vars);
		draw_Character(vars);
	}
	return (0);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, Color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color.value;
}

void	my_mlx_put_image(t_data *data, int x, int y, Color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color.value;
}

int	main(void)
{
	t_vars	vars;
	vars.chac.x = 1;
	vars.chac.y = 1;
	/* vars.maps[0] = (int[]){1, 1, 1, 1, 1, 1, 1};
	vars.maps[1] = (int[]){1, 0, 0, 0, 0, 0, 1};
	vars.maps[2] = (int[]){1, 1, 1, 1, 1, 1, 1}; */
	vars.max_x = 20;
	vars.max_y = 20;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.max_x * TILE_SIZE, vars.max_y * TILE_SIZE, "so_long");
	draw_background(&vars);
	draw_wall(&vars);
	draw_Character(&vars);
	mlx_hook(vars.win, 2, 1L<<0, keyhandle, &vars);
	mlx_hook(vars.win, 17, 0L, exitApp, &vars);
	mlx_loop(vars.mlx);
	return (0);
}