# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/16 17:11:58 by agiordan     #+#   ##    ##    #+#        #
#    Updated: 2019/02/06 20:08:06 by agiordan    ###    #+. /#+    ###.fr      #
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
			key_hook.c \
			mouse_hook.c \
			draw.c
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ_PATH = obj
OBJ_NAME = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

CC = gcc
FLAGS = -Wall -Werror -Wextra
PPFLAGS = -Iinclude

INCLUDE_PATH = include
LIB1 = libft
LIB2 = minilibx_macos
LIB = $(LIB1)/$(LIB1).a $(LIB2)/libmlx.a

FRAMEWORK = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIB1)
		make -C $(LIB2)
		$(CC) $(LIB) $(FRAMEWORK) $^ -o $@
		$(CC) $(FLAGS) launcher.c -o launcher

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		$(CC) $(FLAGS) $(PPFLAGS) -c $< -o $@

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
		norminette $(SRC)
		norminette $(INCLUDE_PATH)/*.h

.PHONY: all, clean, flcean, re
