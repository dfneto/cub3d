# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davifern <davifern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 11:46:48 by davifern          #+#    #+#              #
#    Updated: 2024/08/27 09:51:40 by davifern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################## VARIABLES DEFINITIONS ###############################
NAME = cub3d
MAKE = make --no-print-directory
HEADER = inc/cub3d.h
SRC_PARSER = src/parser/check_closed.c src/parser/check_map.c src/parser/clean_utils.c src/parser/ft_perror.c src/parser/ft_strtok.c \
			src/parser/image_utils.c src/parser/open_utils.c src/parser/parse_input.c \
			src/parser/parse_textures.c src/parser/read_utils.c src/parser/safe_allocation.c \
			src/parser/safe_allocation2.c src/parser/fake_split.c src/parser/invert_image.c
SRC = src/main.c src/inits.c src/errors.c src/draw_elements.c src/utils.c src/hooks.c \
		src/bresenham.c src/utils2.c src/render.c src/textures.c \
		src/texture_test.c  src/draw_everything_3d_with_texture.c \
		$(SRC_PARSER)
# src/dda.c src/draw_everything_3d.c 
OBJ_DIR = obj
OBJ_DIR_PARSER = obj/parser
DEP_DIR = dep
DEP_DIR_PARSER = dep/parser
DIR_MLX = mlx
CC = gcc
CFLAGS += -Wextra -Werror -Wall -MMD -g -I mlx -I inc -I libft

# This line itself doesn't actually generate the object files; it just sets up the 
# names that will be used when the object files are generated
OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
DEPS = $(SRC:src/%.c=$(DEP_DIR)/%.d)

################################# RULES ####################################### 
# -C <path> option. This changes the current path to the path '<path>', -s silent
all: 
	$(MAKE) -C libft
	$(MAKE) -sC mlx
	$(MAKE) $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	$(CC) $(OBJS) -O3 -Lmlx -Llibft -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# This is a pattern rule that specifies to make how to build an object file (.o) from a 
# corresponding source file (.c). It also depends on the $(HEADER) file and Makefile, meaning the
# object files will be recompiled if the header file or the Makefile changes.
# $(CC) $(CFLAGS) -c $< -o $@: This is the command that actually compiles each .c 
# file into an .o file. $< is the first dependency (the .c file in this case) and $@ 
# is the target (the .o file).
$(OBJ_DIR)/%.o: src/%.c $(HEADER) Makefile | $(OBJ_DIR) $(DEP_DIR) $(OBJ_DIR_PARSER) $(DEP_DIR_PARSER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR)/$*.d

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
