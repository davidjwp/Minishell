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
# include <sys/stat.h>
# include <sys/types.h>
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
	word 0
	separator 1
	quotes 2
	exit status 3
	append redirection 4
	heredoc 5
	argument 6
	operator 7
	redirection left 8
	variable 9
	pipeline 10
	builtin 11
	redirection right 12
	command 13
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

enum e_clflags{
	CL_FDS = 1,
	CL_TRE = 2,
	CL_ENV = 4,
	CL_INP = 8,
	CL_HIS = 16,
	CL_CL = 32,
	CL_ALL = 63,
};

enum e_ResFDflags{
	RES_IN = 1,
	RES_OUT = 2,
	RED_PIP = 4,
	RED_RED = 8,

};

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
	char				**cl;
}	t_env;

typedef struct PipeStruct{
	pid_t	r_pid;
	pid_t	l_pid;
	int		pipe_fd[2];
}	t_pipe;

typedef struct RedirectionStruct{
	int	in;
	int	out;
}	t_red;

typedef struct FileDescriptors{
	int						fd;
	struct FileDescriptors	*next;
}	t_fds;

typedef struct CleanUp{
	t_fds	*fds;
	t_astn	*tree;
	t_env	*env;
	char	*input;
}	t_cleanup;

typedef struct ExecuteArgumentStruct{
	char	*_path;
	char	**_envp;
	char	**argv;
}	t_exe;

#endif
