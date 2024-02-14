NAME = so_long

SRC =	src/main.c src/map.c src/player.c src/tile.c src/utils.c\
		src/map_utils.c src/map_check.c src/map_wall_check.c\
		lib/get_next_line/get_next_line.c lib/get_next_line/get_next_line_utils.c

SRC_DIR	=	./
SRCS	=	${addprefix ${SRC_DIR}, ${SRC}}
OBJ		=	${SRCS:.c=.o}
NAME	=	so_long
CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

all: ${NAME}

.c.o: 		ft_printf.h
	${CC} ${CFLAGS} -I . -c $< -o $@

all: ${NAME}

libftprintf.a: 
	make -C lib/ft_printf
	mv lib/ft_printf/libftprintf.a libftprintf.a

libmlx.a: 
	cmake -S lib/mlx -B mlxbuild  -DDEBUG=1
	cmake --build mlxbuild -j4
	mv mlxbuild/libmlx42.a libmlx.a

${NAME}: libftprintf.a libmlx.a ${OBJ}
	${CC} -L. -lmlx -lftprintf -L"/opt/homebrew/Cellar/glfw/3.3.9/lib/" -lglfw ${CFLAGS} ${OBJ} -o ${NAME}

clean: 
	rm -f ${OBJ}
	rm -rf mlxbuild
	make -C lib/ft_printf clean

fclean: clean
	rm -f libftprintf.a
	rm -f libmlx.a
	rm -f ${NAME}

norminette:
	python3 -m norminette src/*.c src/*.h
	python3 -m norminette lib/get_next_line/*.c lib/get_next_line/*.h
	python3 -m norminette lib/ft_printf/*.c lib/ft_printf/*.h
	python3 -m norminette lib/ft_printf/libft/**/*.c lib/ft_printf/libft/**/*.h

re: clean all
