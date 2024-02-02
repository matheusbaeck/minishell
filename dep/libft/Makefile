# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: math <math@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 13:33:25 by smagniny          #+#    #+#              #
#    Updated: 2024/02/02 19:17:39 by math             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc -Wall -Werror -Wextra #-fsanitize=address
SRCS_DIR = ./src
OBJS_DIR = .obj
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(SRCS))

ERASE = rm -rf

## COLORS ##
END = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[1;37m

## RULES ##
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE) ◎ $(YELLOW)Creating library   $(RED)→   $(WHITE)$(NAME)$(END)"
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Library $(NAME) created$(END)"


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(WHITE)$< $(END)"
	@$(CC) -c -o $@ $<

## CLEANING ##
clean:
	@$(RM) -r $(OBJS_DIR)
	@echo "$(GREEN)$(NAME): $(RED)→ $(BLUE) Cleaning... $(END)"
	@echo "$(GREEN)$(NAME): $(RED)→ $(YELLOW) the files(*.o) were deleted $(END)"


fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME): $(RED) → $(BLUE)was deleted$(END)"

re: fclean all

.PHONY: all re clean fclean

