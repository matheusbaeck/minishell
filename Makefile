# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: math <math@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 10:25:10 by mohafnh           #+#    #+#              #
#    Updated: 2024/01/19 18:32:32 by math             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMP
NAME = minishell
CC = gcc -Wall -Werror -Wextra -fsanitize=address -g
SRC_DIR = ./src
OBJ_DIR = .obj
EXT_LIBS = -lreadline
PATH_LIBFT = $(SRC_DIR)/include/libft

SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

## COLORS ##
END = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[1;37m

## RULES ##
all: $(NAME)

libft:
	@echo "$(NAME): $(BLUE)Generating... Just a minute$(RESET)"
	@make -sC $(PATH_LIBFT)
	@echo "$(NAME): $(GREEN)Done!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(WHITE)$< $(END)"
	@$(CC) -c -o $@ $<

$(NAME): libft $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) -lreadline $(PATH_LIBFT)/libft.a
	clear
	@echo "$(GREEN)You Created $(NAME)$(END)"

## CLEANING ##
clean:
	@$(RM) -r $(OBJ_DIR)
	@make clean -sC $(PATH_LIBFT)
	@echo "$(GREEN)$(NAME): $(RED)→ $(BLUE) Cleaning... $(END)"
	@echo "$(GREEN)$(NAME): $(RED)→ $(YELLOW) the files(*.o) were deleted $(END)"

## REMOVING .O FILES AND .A FILES ##
fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC $(PATH_LIBFT)
	@echo "$(GREEN)$(NAME): $(RED) → $(BLUE)was deleted$(END)"

## REMOVING AND RUNNING ##
re: fclean all

.PHONY: all libft re clean fclean norm