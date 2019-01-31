# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/01/16 17:11:58 by agiordan     #+#   ##    ##    #+#        #
#    Updated: 2019/01/17 06:58:04 by agiordan    ###    #+. /#+    ###.fr      #
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
		arbre.c \
		hook.c \
		draw.c
OBJ = $(SRC:%.c=%.o)

COMPIL = gcc
FLAG = -Wall -Werror -Wextra -lXext -lX11

LIBFT = libft
MLX = minilibx
LIB_MLX = libmlx
INCLUDE = $(LIBFT)/$(LIBFT).a $(MLX)/$(LIB_MLX).a

FRAMEWORK = #-framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT)
		#make -C $(MLX)
		$(COMPIL) $(FLAG) $(OBJ) $(FRAMEWORK) $(INCLUDE) -o $(NAME)
		$(COMPIL) $(FLAG) $(LAUNCHER).c $(INCLUDE) -o $(LAUNCHER)

clean:
		rm -f $(OBJ)
		make clean -C $(LIBFT)
		#make clean -C $(MLX)

fclean: clean
		rm -f $(NAME)
		make fclean -C $(LIBFT)
		#make fclean -C $(MLX)

re: fclean all
