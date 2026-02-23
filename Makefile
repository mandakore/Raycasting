# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/10 13:57:51 by sohyamaz          #+#    #+#              #
#    Updated: 2026/02/23 14:22:44 by sohyamaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =========================
# Target
# =========================
NAME	= cub3D
LFLAGS = -L./include/mlx -lmlx -lXext -lX11 -lm
INCLUDES = -I./include

# =========================
# Compiler
# =========================
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g

# =========================
# Paths
# =========================
INC_DIR	= ./include
MLX_DIR	= ./include/mlx
MLX_LIB	= $(MLX_DIR)/libmlx.a

# =========================
# Sources
# =========================
SRCS	= src/apply_shading.c \
		  src/calc_move.c \
		  src/calc_texture.c \
		  src/calc_wall_height.c \
		  src/dda.c \
		  src/dup_parsed_arguments.c \
		  src/init_map.c \
		  src/init_player.c \
		  src/init_raycast.c \
		  src/key.c \
		  src/load_texture.c \
		  src/main.c \
		  src/minimap.c \
		  src/move.c \
		  src/parse.c \
		  src/parse_closed_map.c \
		  src/parse_color_code.c \
		  src/parse_config_informations.c \
		  src/parse_map_data.c \
		  src/parse_texture_file.c \
		  src/print_config_error.c \
		  src/print_error.c \
		  src/print_init_error.c \
		  src/print_mapdata_error.c \
		  src/raycasting.c \
		  src/texture.c \
		  src/utils_for_allocation.c \
		  src/utils_for_duplication.c \
		  src/utils_for_free.c \
		  src/utils_for_game.c \
		  src/utils_for_minimap.c \
		  src/utils_for_parsing.c \
		  src/utils_for_parsing_map.c \
		  src/utils_for_read.c


OBJS	= $(SRCS:%.c=%.o)

# =========================
# Includes / Libs
# =========================
INCLUDES	= -I$(INC_DIR) -I$(MLX_DIR)
LDFLAGS		= -L$(MLX_DIR)
LDLIBS		= -lmlx -lXext -lX11 -lm

# =========================
# Rules
# =========================
all: $(NAME)

# Link

$(OBJS): $(INC_DIR)/cub3D.h

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

# Compile
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build MLX if needed
$(MLX_LIB):
	@if [ ! -f "$(MLX_DIR)/Makefile" ] && [ ! -f "$(MLX_DIR)/makefile" ]; then \
		rm -rf "$(MLX_DIR)"; \
		git clone https://github.com/42Paris/minilibx-linux.git "$(MLX_DIR)"; \
	fi
	$(MAKE) -C "$(MLX_DIR)"

# =========================
# Clean rules
# =========================
clean:
	rm -f $(OBJS)
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re

# =========================
# Test (optional isolated)
# =========================
TEST_NAME = autotest
TEST_SRCS = $(SRCS:src/main.c=test/main.c)
TEST_OBJS = $(TEST_SRCS:%.c=%.o)

$(TEST_NAME): $(MLX_LIB) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

test: $(TEST_NAME)
	./bin/test.sh
	$(MAKE) testfclean

# Test clean (object only)
testclean:
	rm -f $(TEST_OBJS)

# Test full clean (binary + objs)
testfclean: testclean
	rm -f $(TEST_NAME)

.PHONY: test testclean testfclean
