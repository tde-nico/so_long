# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tde-nico <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 17:37:01 by tde-nico          #+#    #+#              #
#    Updated: 2022/02/11 11:32:17 by tde-nico         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./srcs/main.c \
				./srcs/map.c \
				./srcs/render.c \
				./srcs/animations.c \
				./srcs/end.c \
				./srcs/utils.c
LIBFT		=	make -C libft
MINILIBX	=	make -C mlx
LIB			=	libft/libft.a
MLX			=	mlx/libmlx.a
OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
LINKER		=	-framework OpenGL -framework AppKit
INCLUDE		=	-I include
NAME		=	so_long

all: $(NAME)

$(NAME): $(OBJS) libft minilibx
	$(CC) $(FLAGS) $(LINKER) $(INCLUDE) $(OBJS) $(LIB) $(MLX) -o $(NAME)

libft:
	make -C libft

minilibx:
	make -C mlx

clean:
	rm -rf $(OBJS)
	make clean -C libft
	make clean -C mlx

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

.c.o:
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

re:	fclean all

.PHONY: all clean fclean re so_long libft mlx
