# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/04 12:27:55 by tcakir-y          #+#    #+#              #
#    Updated: 2025/03/20 20:34:59 by tcakir-y         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#git submodule add https://github.com/42paris/minilibx-linux.git
#git submodule update --init --recursive

NAME = so_long

INC_DIR = includes
LIBFT_DIR = libft
MLX_DIR = minilibx-linux
SRC_DIR = src
OBJ_DIR = objs

CC = gcc
CCFLAGS = -Wall -Werror -Wextra -I$(INC_DIR) -I$(MLX_DIR) -g
MLX_FLAGS = -L$(MLX_DIR) -lmlx -I$(MLX_DIR) -O3 -lX11 -lXext -lm

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx_Linux.a

SRCS =	main.c\
		check_map.c\
		map_read.c\
		ft_free.c\
		check_valid_path.c\
		mlx_func.c\
		mlx_utils.c\
		movements.c\
		enemy.c
		
SRC = $(addprefix $(SRC_DIR)/, $(SRCS))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CCFLAGS) -c $< -o $@

$(LIBFT):
		@make -C $(LIBFT_DIR)

$(MLX):
		@git submodule update --init --recursive
		@make -C $(MLX_DIR)

	
$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) \
	-L $(LIBFT_DIR) -lft $(MLX_FLAGS) -no-pie

clean:
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT_DIR)
		@make clean -C $(MLX_DIR)
		@echo "Dependencies & Objects removed"
fclean: clean
		@rm -f $(NAME)
		@rm -f $(LIBFT_DIR)/libft.a
		@echo "Programs removed"

re: fclean all

.PHONY: all clean fclean re 