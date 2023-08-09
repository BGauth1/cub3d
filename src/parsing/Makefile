# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lamasson <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 13:34:21 by lamasson          #+#    #+#              #
#    Updated: 2023/08/01 18:01:36 by lamasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -g

RM		= rm -rf

NAME	= cube3D

SRCS	= ft_parsing.c \
		  ft_parsing_color.c \
		  ft_parsing_color_error.c \
		  ft_parsing_texture.c \
		  ft_parsing_texture_error.c \
		  ft_init_struct.c \
		  ft_parsing_map.c \
		  ft_parsing_map_utils.c \
		  ft_parsing_map_error.c \
		  main.c

OBJS	= ${SRCS:%.c=%.o}

LIBFT	= ./libft

LIB		= ./libft/libft.a

%.o: %.c
		@${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

${NAME}: ${OBJS} 
		make bonus -C ${LIBFT}
		${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}

clean:
		make -s -C ${LIBFT} clean
		${RM} ${OBJS}

fclean: clean
		make -s -C ${LIBFT} fclean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re

