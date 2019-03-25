# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/16 17:11:58 by agiordan     #+#   ##    ##    #+#        #
#    Updated: 2019/03/25 17:43:55 by agiordan    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fractol

SRC_PATH = src
SRC_FILES =	fractol.c \
			flags.c \
			mandelbrot.c \
			julia.c \
			burningship.c \
			tree.c \
			triangle.c \
			tapis.c \
			star.c \
			fern.c \
			pi.c \
			key_hook.c \
			mouse_hook.c \
			draw.c \
			colors.c
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ_PATH = obj
OBJ_NAME = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INCLUDE_PATH = include
CC = gcc
FLAGS = -Wall -Werror -Wextra -I$(INCLUDE_PATH)

FRAMEWORK = -framework OpenGL -framework AppKit

LIB1 = libft
LIB2 = minilibx_macos
LIB = $(LIB1)/$(LIB1).a $(LIB2)/libmlx.a $(FRAMEWORK)

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIB1)
		make -C $(LIB2)
		$(CC) $(FLAGS) $(LIB) $^ -o $@
		$(CC) $(FLAGS) $(LIB) $(SRC_PATH)/launcher.c -o launcher

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		$(CC) $(FLAGS) -c $< -o $@

clean:
		make clean -C $(LIB1)
		make clean -C $(LIB2)
		@rm -rf $(OBJ_PATH) 2> /dev/null || true

fclean: clean
		make fclean -C $(LIB1)
		make fclean -C $(LIB2)
		rm -f $(NAME)
		rm -f launcher

re: fclean all

norme:
		@norminette $(LIB1)
		@norminette $(SRC_PATH)
		@norminette $(INCLUDE_PATH)

.PHONY: all, clean, flcean, re
