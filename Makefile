# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/16 17:11:58 by agiordan     #+#   ##    ##    #+#        #
#    Updated: 2019/02/06 16:43:35 by agiordan    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = fractol
LAUNCHER = launcher

SRC =	fractol.c \
		flags.c \
		mandelbrot.c \
		julia.c \
		burningship.c \
		tree.c \
		key_hook.c \
		mouse_hook.c \
		draw.c
OBJ = $(SRC:%.c=%.o)

CC = gcc
FLAG = -Wall -Werror -Wextra

LIBFT = libft
MLX = minilibx_macos
LIB_MLX = libmlx
INCLUDE = $(LIBFT)/$(LIBFT).a $(MLX)/$(LIB_MLX).a

FRAMEWORK = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		make -C $(MLX)
		$(CC) $(FLAG) $(OBJ) $(FRAMEWORK) $(INCLUDE) -o $(NAME)
		$(CC) $(FLAG) $(LAUNCHER).c $(INCLUDE) -o $(LAUNCHER)

clean:
		rm -f $(OBJ)
		make clean -C $(LIBFT)
		make clean -C $(MLX)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)
		make fclean -C $(MLX)

re: fclean all
