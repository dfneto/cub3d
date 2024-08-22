# //TODO: remover o -MMD e ver a diferença de com e sem ele (sei que ele gera uns .d)
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davifern <davifern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/05 11:46:48 by davifern          #+#    #+#              #
#    Updated: 2024/07/05 13:01:56 by davifern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################## VARIABLES DEFINITIONS ###############################
NAME = cub3d
MAKE = make --no-print-directory
HEADER = inc/cub3d.h
SRC = src/main.c src/inits.c src/errors.c src/draw_elements.c src/utils.c src/hooks.c \
		src/bresenham.c src/utils2.c  \
		src/texture_test.c  \
		#src/dda.c src/draw_everything_3d.c src/draw_everything_3d_with_texture.c
OBJ_DIR = obj
DEP_DIR = dep
DIR_MLX = mlx_linux
CC = gcc
CFLAGS += -Wextra -Werror -Wall -g  -I/usr/include -Imlx_linux -Iinc -O3

# This line itself doesn't actually generate the object files; it just sets up the 
# names that will be used when the object files are generated
OBJS = $(SRC:src/%.c=$(OBJ_DIR)/%.o)
DEPS = $(SRC:src/%.c=$(DEP_DIR)/%.d)

################################# RULES ####################################### 
# -C <path> option. This changes the current path to the path '<path>', -s silent
all: 
	$(MAKE) -sC mlx_linux
	$(MAKE) $(NAME)

# This is a pattern rule that specifies to make how to build an object file (.o) from a 
# corresponding source file (.c). It also depends on the $(HEADER) file and Makefile, meaning the
# object files will be recompiled if the header file or the Makefile changes.
# $(CC) $(CFLAGS) -c $< -o $@: This is the command that actually compiles each .c 
# file into an .o file. $< is the first dependency (the .c file in this case) and $@ 
# is the target (the .o file).
$(OBJ_DIR)/%.o: src/%.c $(HEADER) Makefile | $(OBJ_DIR) $(DEP_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP -MF $(DEP_DIR)/$*.d

$(NAME): $(OBJS) $(HEADER) Makefile
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(DEP_DIR):
	mkdir -p $(DEP_DIR)
	
clean:
	rm -f $(OBJ_DIR)/*.o $(DEP_DIR)/*.d
	rm cub3d
	rm -rf *.dSYM
	@$(MAKE) clean -sC $(DIR_MLX)

fclean: clean
	rm -f $(NAME)
	rm -f *.gch

re: fclean all

-include $(DEPS)

.PHONY: all bonus clean fclean re