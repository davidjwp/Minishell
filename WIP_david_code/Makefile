# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djacobs <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 16:35:37 by djacobs           #+#    #+#              #
#    Updated: 2023/09/19 16:35:38 by djacobs          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc

NAME			= minitest

CFLAGS			= -g3 -Wall -Wextra -Werror

LINKER			= -L/usr/include -lreadline

SRCS			= parser/lexerutils_A.c parser/lexerutils_B.c \
				parser/lexerutils_C.c parser/utils.c parser/create_ast.c parser/lexerutils_D.c

OBJS			= $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) Minishell.h $(OBJS) $(LINKER) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all