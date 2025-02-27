# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 23:38:06 by gfrancoi          #+#    #+#              #
#    Updated: 2025/02/27 23:43:22 by gfrancoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				fdf
CFLAGS =			-Wall -Wextra -Werror
LIBFT =				./libft/libft.a
MINILIBX =			./minilibx-linux/libmlx.a

SRCS = \
	main.c

OBJ_DIR = obj

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	cc -g3 $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX)

$(LIBFT):
	make -C ./libft/

$(MINILIBX):
	make -C ./minilibx-linux/

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	cc -g3 $(CFLAGS) -c -o $@ $^

clean:
	make clean -C ./libft/
	make clean -C ./minilibx-linux/
	rm -fr $(OBJ_DIR)

fclean: clean
	make fclean -C ./libft/
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re