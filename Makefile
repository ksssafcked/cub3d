# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 11:50:17 by qudomino          #+#    #+#              #
#    Updated: 2025/01/18 15:53:07 by lsaiti           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lX11 -lXext -lmlx -lm
SRC = src/main.c src/parser.c utils/gnl.c utils/gnl_utils.c src/print.c \
	  utils/ft_utils.c src/parser_config.c utils/ft_split.c src/raycasting.c \
	  src/handler.c src/get_info.c src/direction.c src/parser_utils.c \
	  src/init.c src/change.c src/parser_textures.c
OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME} ${LDFLAGS}

clean :
	rm -rf ${OBJ}

fclean : clean
	rm -rf ${NAME}

re : fclean all
