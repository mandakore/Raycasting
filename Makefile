NAME = game
CC = cc
OBJ = $(SRC:.c=.o)

LFLAGS = aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
INCLUDES = includes/mlx/libmlx.a
SRC = src/main.c

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./includes/mlx
	make -C ./includes/mlx
##要検討--fatal: destination path './includes/mlx' already exists and is not an empty directory.
##make: *** [Makefile:10: mlx] Error 128

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)


clean:
	rm -f $(OBJS)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)







re: fclean all


.PHONY: all clean fclean re