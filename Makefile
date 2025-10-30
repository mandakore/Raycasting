NAME = game
CC = cc
OBJ = $(SRC:.c=.o)

LFLAGS = -L./include/mlx -lmlx -lXext -lX11 -lm
INCLUDES = -I./include
SRC = src/main.c src/utils.c

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./include/mlx
	make -C ./include/mlx

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $(NAME) $(INCLUDES) $(LFLAGS)


clean:
	rm -f $(OBJ)

fclean:
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all


.PHONY: all clean fclean re