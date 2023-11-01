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

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT	"$> "

//FLAGS
# define C_PIPE 0
# define C_RED 1

# define G_ERROR 0
# define IT_SEP 0
# define IT_TOK	1

#ifndef MINISHELL_H
	volatile int	g_signal;
#endif

enum e_builtin{
	ECHO = 22,
	CD = 33,
	PWD = 44,
	EXPORT = 55,
	UNSET = 66,
	ENV = 77,
	EXIT = 88
};

/*
	token types:
	word
	separator
	quotes
	exit status
	append redirection
	heredoc
	argument
	operator
	redirection left
	variable
	pipeline
	builtin
	redirection right
	command
	do not touch this, it's built like this on purpose
*/
enum e_type{
	WORD,
	SEPR,
	QUOT,
	EXST,
	APRD,
	HERD,
	ARGT,
	OPER,
	REDL,
	VARE,
	PIPE,
	BUIT,
	REDR,
	COMD,
};	

typedef struct PipexStruct{
	int		i;
	int 	o;
	pid_t	pid;
	int		_int;
}

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
	t_token							**token;
	int								type;
	struct AbstractSyntaxTreeNode	*parent;
	struct AbstractSyntaxTreeNode	*left;
	struct AbstractSyntaxTreeNode	*right;
}				t_astn;

typedef struct Cmd_Struct_Nodes{
	t_astn	*parent;
	t_astn	*node;
}				t_cms;

//LEXER++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//lexerutils_A
int			type(const char *s, size_t i);
bool		_pipe(const char *input);
bool		_red(const char *input);
bool		cmp(char *content, const char *input);
bool		check_spec(const char *input, size_t *i);

//lexerutils_B
bool		check_quote(const char *input, size_t *i);
int			built_in(const char *input);
int			get_token_type(char	*token);
bool		it_token(const char *input, size_t *i, int flag);
char		*get_content(const char *input, size_t *index, size_t *len);

//lexerutils_C
t_token		*get_token(const char *input, size_t *l_ind, t_token *token);
int			nbr_token(const char *input);
void		free_tok(t_token **tokens, int last);
void		free_cmd_node(t_astn *cmd);
void		free_node(t_astn *red);

//lexerutils_D
int			init_node(t_astn *node, int nbr, t_astn *p, int *error);
const char	*cut_r(const char *input, int flag);
const char	*cut_l(const char *input, int flag);
int			get_node_type(const char *input, size_t *g_ind);
void		free_tree(t_astn *node);

t_astn		*ast_cmd(const char *input, size_t *index, t_cms c, int *error);

void		err_msg(char *msg);
char		**tokenize(char *s, int *tokens_n, int tokens_i);
int			parser(char *input);
t_astn		*create_ast(const char *input, size_t *i, int *error, t_astn *p);

#endif