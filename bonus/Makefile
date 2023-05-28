CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = cub3d.a
PROG = cub3d
SOURCES = main.c utils/frame.c utils/getnextline.c utils/draw.c utils/dda.c utils/bonus_utils3.c utils/bonus_utils1.c utils/bonus_utils2.c utils/open_door.c \
	utils/ft_split.c	utils/ft_atoi.c	utils/ft_itoa.c utils/bonus_utils4.c utils/ft_strjoin.c\
	utils/check_data/check_map.c utils/set_data/set_data.c 	utils/ft_strtrim.c	\

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

