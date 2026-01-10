# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sohyamaz <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/10 13:57:51 by sohyamaz          #+#    #+#              #
#    Updated: 2026/01/10 14:33:06 by sohyamaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =========================
# Target
# =========================
NAME	= game

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
SRCS	= src/main.c \
		  src/utils.c \
		  src/key.c

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
