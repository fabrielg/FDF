# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 23:38:06 by gfrancoi          #+#    #+#              #
#    Updated: 2025/03/31 20:34:56 by gfrancoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				fdf
CFLAGS =			#-Wall -Wextra -Werror
LIBFT =				./libft/libft.a
MINILIBX =			./mlx/libmlx.a

SRCS = \
	main.c\
	parsing.c\
	draw_line.c\
	matrix.c\
	fdf.c\
	isometric.c\
	projection.c\
	window_utils.c

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	cc -g3 $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) -Lmlx -lmlx -lX11 -lXext -lm

$(LIBFT):
	make -C ./libft/

$(MINILIBX):
	make -C ./mlx/

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	cc -g3 $(CFLAGS) -Imlx -O3 -c -o $@ $^

clean:
	make clean -C ./libft/
	make clean -C ./mlx/
	rm -fr $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re