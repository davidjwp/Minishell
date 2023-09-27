/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:12:56 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/15 21:12:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT	"$> "
# define G_ERROR 0
# define IT_SEP 0
# define IT_TOK	1

volatile int	g_signal;

//it is a multiplied of BUILTIN so as to not confuse it with other types
enum e_builtin{
	ECHO = 22,
	CD = 33,
	PWD = 44,
	EXPORT = 55,
	UNSET = 66,
	ENV = 77,
	EXIT = 88
};

enum e_type{
	SEPARATOR,
	QUOTES,
	EXSTAT,
	HEREDOC,
	APREDIR,
	ARGUMENT,
	OPERATOR,
	VARIABLE,
	PIPE,
	COMMAND,
	BUILTIN,//11 should be the last enum to not reach other
	WORD = 0
};	

typedef struct s_token{
	int	type;
	// int		pos;
	size_t	len;
	char	*content;
}			t_token;

typedef struct s_lst{
	t_token	*token;
	struct s_lst	*next;	
}				t_tlst;

typedef struct AbstractSyntaxTreeNode{
	t_token	*token;
	struct AbstractSyntaxTreeNode	*parent;
	struct AbstractSyntaxTreeNode	*children; 
}				t_astnode;

typedef struct parseTreeNode{
	int		tokcnt;
	struct parseTreeNode	*parent;
	struct parseTreeNode	*children;
}				t_ptn;

void		free_tokens(char **tokens_s);
void		err_msg(char *msg);
char		**tokenize(char *s, int *tokens_n, int tokens_i);
int			parser(char *input);

#endif