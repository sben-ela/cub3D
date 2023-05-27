CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
NAME = cub3d.a
PROG = cub3d
SOURCES = main.c utils/getnextline.c utils/mandatory_utils1.c utils/frame.c utils/draw.c utils/dda.c  utils/mandatory_utils2.c	\
utils/ft_split.c	utils/ft_atoi.c	utils/mandatory_utils3.c \
		utils/check_data/check_map.c	utils/set_data/set_data.c 	utils/ft_strtrim.c	\

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME) clean

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	cc	$(CFLAGS)  $(OBJECTS) -L../minilibx -lmlx -framework OpenGL -framework AppKit -o $(PROG)
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME) $(PROG)

re: fclean all

