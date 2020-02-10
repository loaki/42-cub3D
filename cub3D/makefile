# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 17:09:22 by jfeuilla          #+#    #+#              #
#    Updated: 2020/02/10 17:54:18 by jfeuilla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re norme

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = cub3D

SRC_PATH = ./src
INC_PATH = ./src
OBJ_PATH = ./obj
OBJLIB_PATH = ./obj

SRC_NAME =	ft_bmp.c\
			ft_check.c\
			ft_clear.c\
			ft_clear2.c\
			ft_draw.c\
			ft_gun.c\
			ft_health.c\
			ft_init_image.c\
			ft_init_image2.c\
			ft_move.c\
			ft_parsing.c\
			ft_parsing2.c\
			ft_rotate.c\
			ft_size_wall.c\
			ft_sprite.c\
			ft_view.c\
			get_next_line.c\
			get_next_line_utils.c\
			main.c

INC_NAME = 	cub3d.h\
			get_next_line.h

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Wextra -Werror -o ${NAME} -framework OpenGL -framework AppKit ./src/libmlx.a ${OBJ}

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ./obj $(NAME)

re: fclean all

norme:
	@norminette $(SRC) $(INC)
