NAME = so_long

SRCS = src/main.c

all: ${NAME}

libmlx.a: 
	@make -C lib/mlx
	@mv lib/mlx/libmlx.a libmlx.a

${NAME}: libmlx.a
	clang -fsanitize=address -lm -L. -lmlx -framework OpenGL -framework AppKit ${SRCS} -o ${NAME}

clean:
	rm ${NAME}

re: clean all
