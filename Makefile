NAME = so_long

SRCS = src/main.c src/map.c lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

all: ${NAME}

libmlx.a: 
	@make -C lib/mlx
	@mv lib/mlx/libmlx.a libmlx.a

${NAME}: libmlx.a
	clang -fsanitize=address -lm -L. -lmlx -framework OpenGL -framework AppKit -g ${SRCS} -o ${NAME}

clean:
	rm ${NAME}

re: clean all
