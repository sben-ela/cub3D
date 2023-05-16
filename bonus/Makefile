CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
NAME = cub3d.a
PROG = cub3d
SOURCES = main.c utils/frame.c utils/getnextline.c utils/cub_utils.c utils/dda.c utils/draw.c  utils/ft_itoa.c utils/ft_strjoin.c utils/open_door.c
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

