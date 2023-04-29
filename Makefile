CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
NAME = cub3d.a
PROG = cub3d
SOURCES = cub.c frame.c getnextline.c cub_utils.c dda.c draw.c open_door.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	cc	$(CFLAGS)  $(OBJECTS) -lmlx -framework OpenGL -framework AppKit  -o $(PROG)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME) $(PROG)

re: fclean all