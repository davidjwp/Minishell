/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SH_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:12:56 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/15 21:12:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_STRUCTS_H
# define SH_STRUCTS_H

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
# define ABS_PATHS "/usr/bin:/usr/sbin:/bin:/sbin"

//FLAGS
# define C_PIPE 0
# define C_RED 1

# define G_ERROR 0
# define IT_SEP 0
# define IT_TOK	1

extern volatile int	g_signal;

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



typedef struct ExecuteStruct{
	pid_t	pid;
	int		status;
}	t_exe;

typedef struct s_token{
	int		type;
	size_t	len;
	char	*content;
}	t_token;

typedef struct AbstractSyntaxTreeNode{
	t_token							**token;
	int								type;
	struct AbstractSyntaxTreeNode	*parent;
	struct AbstractSyntaxTreeNode	*left;
	struct AbstractSyntaxTreeNode	*right;
}	t_astn;

typedef struct Cmd_Struct_Nodes{
	t_astn	*parent;
	t_astn	*node;
}				t_cms;

typedef struct ShellEnvNode{
	char				*name;
	char				*value;
	struct ShellEnvNode	*next;
}	t_env;

typedef struct PipeStruct{
	t_exe		exe;
	char		**args;
	char		**paths;
	char		*pathname;
	int			pipe_fd[2];
}	t_pipe;

typedef struct RedirectionStruct{
	int	in;
	int	out;
}	t_red;

#endif
