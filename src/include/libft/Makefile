# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smagniny <santi.mag777@student.42madrid    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 13:33:25 by smagniny          #+#    #+#              #
#    Updated: 2023/11/30 13:50:16 by smagniny         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_split.c ft_striteri.c ft_itoa.c  ft_strmapi.c ft_strjoin.c ft_strtrim.c ft_substr.c ft_memset.c ft_bzero.c ft_strlen.c ft_atoi.c ft_isdigit.c ft_isalpha.c ft_isprint.c ft_isascii.c ft_isalnum.c ft_memchr.c ft_memcpy.c ft_memcmp.c ft_memmove.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c ft_toupper.c ft_tolower.c ft_strnstr.c ft_strrchr.c ft_strdup.c \
		get_next_line_bonus.c  get_next_line_utils_bonus.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
		ft_printf_char.c \
		ft_printf_int.c \
		ft_printf_str.c \
		ft_printf_utils.c \
		ft_printf.c \
		ft_printf_unsigned.c \
		ssplit.c \
		ft_openfd.c \
		ft_mat.c \
		doublefree.c \
		ft_isspace.c \
		ft_substr_startend.c \
		ft_cpy2dpointer.c

OBJS = ${SRCS:.c=.o}

NAME = libft.a
ERASE = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
%.o : %.c
	gcc -Wall -Werror -Wextra -c $< 
	
clean:
	${ERASE} ${OBJS} ${OBJS_B}
fclean:
	${ERASE} ${OBJS} ${OBJS_B} ${NAME}

re: fclean all

