# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: math <math@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 10:25:10 by mohafnh           #+#    #+#              #
#    Updated: 2024/01/18 23:33:53 by math             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COMP
NAME = minishell
CC = gcc -Wall -Werror -Wextra -fsanitize=address -g
EXT_LIBS = -lreadline
PATH_LIBFT = ./include/libft

SRC =  maintest.c \
	Parser/lexer.c \
	Parser/Tokenizer.c \
	Parser/utils_tokenizer.c \
	Parser/addword.c \
	Parser/word_quoteshandler.c \
	Parser/lst_funcs_node.c \
	Parser/lst_funcs_subnode.c \
	Builtin/cd.c \
	Builtin/echo.c \
	Builtin/env.c \
	Builtin/export.c \
	Builtin/unset.c \
	Builtin/pwd.c \
	Builtin/run_builtins.c \
	Env/Env.c \
	Env/Expansor.c \
	Env/Expansor_utils.c \
	Redir/redir.c \
	External/ft_exec.c \
	Prompt.c \
	Process/process_handler.c

OBJS = ${SRC:.c=.o}
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

%.o : %.c 
	@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(WHITE)$< $(END)"
	@$(CC) -c -o $@ $<

$(NAME): libft $(OBJS)

	@$(CC) -o $(NAME) $(OBJS) -lreadline $(PATH_LIBFT)/libft.a
	clear
	@echo "$(GREEN)You Created $(NAME)$(END)"

## CLEANING ##
clean:
	@$(RM) $(OBJS)
	@make clean -sC $(PATH_LIBFT)
	@echo "$(GREEN)$(NAME): $(RED)→ $(BLUE) Cleaning... $(END)"
	@echo "$(GREEN)$(NAME): $(RED)→ $(YELLOW) the files(*.o) were deleted $(END)"

## REMOVING .O FILES AND .A FILES ##
fclean: clean
	$(RM) $(NAME) $(OBJS) $(libft)
	@make fclean -sC $(PATH_LIBFT)
	@echo "$(GREEN)$(NAME): $(RED) → $(BLUE)was deleted$(END)"

## REMOVING AND RUNNING ##
re: fclean all

.PHONY: all libft re clean fclean norm