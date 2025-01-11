NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lX11 -lXext -lmlx -lm
SRC = src/main.c src/parser.c utils/gnl.c utils/gnl_utils.c src/print_map.c
OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${SRC} -o ${NAME} ${LDFLAGS}

clean :
	rm -rf ${OBJ}

fclean : clean
	rm -rf ${NAME}

re : fclean all