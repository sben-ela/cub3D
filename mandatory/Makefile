# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbarakat <nbarakat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 00:09:29 by nbarakat          #+#    #+#              #
#    Updated: 2023/05/29 00:09:30 by nbarakat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = cub3d.a
PROG = cub3d
SOURCES = main.c utils/getnextline.c utils/mandatory_utils1.c	\
	utils/frame.c	utils/draw.c utils/dda.c	utils/mandatory_utils2.c	\
	utils/ft_split.c	utils/ft_atoi.c	utils/mandatory_utils3.c \
	parsing/check_data/check_characters.c parsing/check_data/check_map.c	\
	parsing/check_data/check_colors.c     parsing/check_data/parsing_utils.c	\
	parsing/check_data/set_data.c	parsing/check_data/check_corners.c    \
	parsing/check_data/parsing_utils1.c	parsing/check_data/check_elements.c   \
	parsing/check_data/parsing_utils2.c 	utils/ft_strtrim.c	\
	parsing/check_data/check_walls.c	\

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	cc	$(CFLAGS)  $(OBJECTS) -L../minilibx -lmlx -framework OpenGL -framework AppKit -o $(PROG)
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME) $(PROG)

re: fclean all

