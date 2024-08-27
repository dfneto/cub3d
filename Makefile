# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davifern <davifern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 11:46:48 by davifern          #+#    #+#              #
#    Updated: 2024/08/27 09:36:23 by davifern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################## VARIABLES DEFINITIONS ###############################
NAME = cub3d
MAKE = make --no-print-directory
HEADER = inc/cub3d.h
SRC_PARSER = src/parser/check_closed.c
SRC = src/main.c src/inits.c src/errors.c src/draw_elements.c src/utils.c src/hooks.c \
		src/bresenham.c src/utils2.c src/render.c src/textures.c \
		src/texture_test.c  src/draw_everything_3d_with_texture.c \
		src/check_map.c \
        src/clean_utils.c src/ft_perror.c src/ft_strtok.c \
        src/image_utils.c src/open_utils.c src/parse_input.c \
        src/parse_textures.c src/read_utils.c src/safe_allocation.c \
        src/safe_allocation2.c src/fake_split.c src/invert_image.c \
		$(SRC_PARSER)
OBJ_DIR = obj
OBJ_DIR_PARSER = obj/parser
DEP_DIR = dep
DEP_DIR_PARSER = dep/parser
DIR_MLX = mlx
CC = gcc
CFLAGS += -Wextra -Werror -Wall -MMD -g -I mlx -I inc -I libft

OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
DEPS = $(SRC:src/%.c=$(DEP_DIR)/%.d)

################################# RULES ####################################### 
all: 
	$(MAKE) -C libft
	$(MAKE) -sC mlx
	$(MAKE) $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	$(CC) $(OBJS) -O3 -Lmlx -Llibft -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# Rule for object files in the main src directory
$(OBJ_DIR)/%.o: src/%.c $(HEADER) Makefile | $(OBJ_DIR) $(DEP_DIR) $(OBJ_DIR_PARSER) $(DEP_DIR_PARSER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR)/$*.d

# Rule for object files in the parser directory
$(OBJ_DIR_PARSER)/%.o: src/parser/%.c $(HEADER) Makefile | $(OBJ_DIR_PARSER) $(DEP_DIR_PARSER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR_PARSER)/$*.d

# Ensure that obj and dep directories are created
$(OBJ_DIR) $(DEP_DIR):
	mkdir -p $@

# Ensure that parser subdirectories are created
$(OBJ_DIR_PARSER) $(DEP_DIR_PARSER): | $(OBJ_DIR) $(DEP_DIR)
	mkdir -p $@

clean:
	rm -f $(OBJS) $(DEPS)
	rm -f $(NAME)

fclean: clean
	$(MAKE) fclean -sC libft
	$(MAKE) clean -sC $(DIR_MLX)
	rm -rf $(OBJ_DIR) $(DEP_DIR)

re: fclean all

-include $(DEPS)

.PHONY: all bonus clean fclean re
