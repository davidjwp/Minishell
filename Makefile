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

SRCS			= main.c parser/parser.c

OBJS			= $(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -g3 Minishell.h $(OBJS) $(LINKER) -o $(NAME)

%.o: %.c
	$(CC) -c -g3 $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

.PHONY: fclean clean all