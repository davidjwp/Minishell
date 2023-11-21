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

INCLUDE			= includes/SH_functs.h includes/SH_structs.h

CFLAGS			= -g3 -Wall -Wextra -Werror

LINKER			= -L/usr/include -lreadline

SRCS			= srcs/parser/lexerutils_A.c srcs/parser/lexerutils_B.c \
				srcs/parser/lexerutils_C.c srcs/parser/utils.c \
				srcs/parser/create_ast.c srcs/parser/lexerutils_D.c \
				srcs/executor/exe.c srcs/executor/exeutils_A.c \
				srcs/executor/exeutils_B.c srcs/cr_env.c srcs/g_utils.c \
				srcs/minishell.c srcs/parser/parser.c \
				srcs/signals/ctrl_signal.c srcs/msgs.c srcs/fds.c

OBJS_DIR		= objs/
OBJS			= $(SRCS:srcs/%.c=$(OBJS_DIR)%.o)#make it so that objs go to objs 

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LINKER) -o $(NAME)

$(OBJS_DIR)%.o: srcs/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all
