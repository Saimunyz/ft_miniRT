# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: swagstaf <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/26 13:36:23 by swagstaf          #+#    #+#              #
#    Updated: 2021/04/01 22:53:31 by swagstaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		miniRT

HEADER =	includes/*.h
LIB =		libft/
MLX =		mlx-linux/
ALL_INC =	-I includes/ -I $(LIB) -I $(MLX)

LFLAGS =	-L libft -lft -L mlx-linux -lmlx -lm -lXext -lX11
FLAGS =		-Wall -Werror -Wextra

OBJ_DIR =	obj/
SRC_DIR =	srcs/

CFILE =		main.c \
			vect_1_utils.c \
			vect_2_utils.c \
			utils_1.c \
			utils_2.c \
			mlx_hooks.c \
			camera.c \
			object.c \
			closest_t.c \
			light.c \
			color.c \
			raytrace_1.c \
			raytrace_2.c \
			sphere.c \
			plane.c \
			square.c \
			cylinder.c \
			triangle.c \
			parse_1.c \
			parse_2.c \
			parse_3.c \
			get_next_line.c \
			ft_strdup_gnl.c \
			bmp_save.c

OFILE =		$(CFILE:.c=.o)

LIBFT_C =	$(LIB)*.c

SRC =		$(addprefix $(SRC_DIR), $(CFILE))

OBJ =		$(addprefix $(SRC_DIR), $(OFILE))

all: $(NAME)

$(OBJ) : $(HEADER)

$(NAME): $(LIB)libft.h $(LIBFT_C) $(OBJ)
		@make -C $(LIB)
		gcc $(FLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

%.o : %.c
		gcc $(FLAGS) $(ALL_INC) -c $< -o $@

clean:
		@make clean -C $(LIB)
		@/bin/rm -f $(OBJ)
		@echo Cleaned $(NAME) object files

fclean: clean
		@make fclean -C $(LIB)
		@/bin/rm -f $(NAME)
		@echo Cleaned $(NAME)

re: fclean all

.PHONY: all clean flcean re
