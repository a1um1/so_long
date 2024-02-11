NAME = so_long

SRCS =	src/main.c src/map.c src/player.c src/tile.c src/utils.c\
		src/map_utils.c src/map_check.c\
		lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

all: ${NAME}

libftprintf.a: 
	make -C lib/ft_printf
	mv lib/ft_printf/libftprintf.a libftprintf.a

libmlx.a: 
	make -C lib/mlx
	mv lib/mlx/libmlx.a libmlx.a

${NAME}: libftprintf.a libmlx.a
	clang -fsanitize=address -lm -L. -lmlx -lftprintf -framework OpenGL -framework AppKit -g ${SRCS} -o ${NAME}

clean:
	rm -f libftprintf.a
	rm -f libmlx.a
	rm -f ${NAME}

re: clean all
