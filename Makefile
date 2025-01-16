# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qudomino <qudomino@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 11:50:17 by qudomino          #+#    #+#              #
#    Updated: 2025/01/14 13:11:10 by qudomino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lX11 -lXext -lmlx -lm
SRC = src/main.c src/parser.c utils/gnl.c utils/gnl_utils.c src/print_map.c \
	  utils/ft_utils.c src/parser_config.c utils/ft_split.c src/raycasting.c
OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${SRC} -o ${NAME} ${LDFLAGS}

clean :
	rm -rf ${OBJ}

fclean : clean
	rm -rf ${NAME}

re : fclean all
