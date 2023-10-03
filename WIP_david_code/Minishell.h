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
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT	"$> "
# define G_ERROR 0
# define IT_SEP 0
# define IT_TOK	1

volatile int	g_signal;

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
	BUILTIN,
	RED_L,
	RED_R,//13
	WORD = 0
};	

typedef struct LexerUtilsStructure{
	int	r;
	int	p;
	int	error;
}				t_lus;

typedef struct s_token{
	int		type;
	size_t	len;
	char	*content;
}			t_token;

typedef struct AbstractSyntaxTreeNode{
	t_token							*token;
	int								type;
	struct AbstractSyntaxTreeNode	*parent;
	struct AbstractSyntaxTreeNode	*left;
	struct AbstractSyntaxTreeNode	*right;
}				t_astnode;

//LEXER++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//lexerutils_A
int		type(char *s);
int		input_pipe(char *input);
int		input_red(char *input);
bool	cmp(char *content, char *input);
bool	check_spec(char *input, size_t *i);

//lexerutils_B
bool	check_quote(char *input, size_t *i);
int		built_in(char *input);
int		get_token_type(char	*token);
bool	it_token(char *input, size_t *i, int flag);
char	*get_content(char *input, size_t *index, size_t *len);

//lexerutils_C
t_token	*get_token(char *input, int *index);
int		nbr_token(char *input);
void	free_tokens(t_token *tokens, int last);
void	free_cmd_node(t_astnode *cmd);
void	free_red_node(t_astnode *red);

void	free_tokens(t_token *tokens, int last);
void	err_msg(char *msg);
char	**tokenize(char *s, int *tokens_n, int tokens_i);
int		parser(char *input);

#endif