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
SRC = src/main.c src/draw_elements.c src/utils.c src/hooks.c src/movements.c
DIR_MLX = mlx_linux
CC = gcc
CFLAGS += -Wextra -Werror -Wall -MMD -g -I mlx -I inc

# This line itself doesn't actually generate the object files; it just sets up the 
# names that will be used when the object files are generated
OBJ = $(SRC:.c=.o)
DEPS = $(SRC:.c=.d)

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
%.o : %.c $(HEADER) Makefile
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -Iinc -O3 -c $< -o $@

$(NAME): $(OBJ) $(HEADER) Makefile
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f *.out src/*.o src/*.d
	rm -rf *.dSYM
	@$(MAKE) clean -sC $(DIR_MLX)

fclean: clean
	rm -f $(NAME)
	rm -f *.gch

re: fclean all

-include $(DEPS)

.PHONY: all bonus clean fclean re
