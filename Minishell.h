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

enum e_type{
	COMMAND,
	ARGUMENT,
	OPERATOR,
	QUOTES,
	VARIABLE,
	SEPARATOR,
	PIPE,
	HEREDOC,
	BUILTIN,
	EXSTAT,
	WORD,
	APREDIR
};	


typedef struct s_token{
	t_type	type;
	int		pos;
	size_t	len;
	char	*content;
}			*t_token;

typedef struct *s_lst{
	t_token	token;
	s_lst	next;	
}				t_tlst;

typedef struct parseTreeNode{
	t_token	token;
	int		tokcnt
	parseTreeNode	parent;
	parseTreeNode	*children;
}				*t_ptr;

void		free_tokens(char **tokens_s);
void		err_msg(char *msg);
char		**tokenize(char *s, int *tokens_n, int tokens_i);
int			parser(char *input);

#endif