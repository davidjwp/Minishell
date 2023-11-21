/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SH_funcs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:12:56 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/11 21:12:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FUNCS_H
# define SH_FUNCS_H

# include "SH_structs.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

//LEXER++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//lexerutils_A
int			type(const char *s, size_t i);
bool		_pipe(const char *input);
bool		_red(const char *input);
bool		cmp(const char *content, const char *input);
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

//create_ast
char		**tokenize(char *s, int *tokens_n, int tokens_i);
t_astn		*create_ast(const char *input, size_t *i, int *error, t_astn *p);

//utils
char		**ft_split(const char *s, char c);
void		free_split(char **split);

//EXEC+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//exe.c
int			open_file(t_astn *tree, t_red *_red, int flag);
int			sh_red(t_astn *tree, t_env *sh_env, t_cleanup *cl);
int			sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl);
int			execute(t_astn *tree, t_env *sh_env, t_cleanup *cl);

//exe_utils_A
char		*cr_pathname(const char *cmd, t_env *sh_env);
char		**cr_envp(t_env *sh_env);
char		**cr_args(t_token **tokens, char *pathname);
char		*envcat(const char *name, const char *value);
char		*strccat(const char *str1, char c, const char *str2);

//exe_utils_B
t_env		*find_env(const char *name, t_env *sh_env);
int			sh_envlen(t_env *sh_env);
void		close_pipe(int *pipe);
void		close_fds(t_fds *fds);
void		wait_pipe(t_pipe p);

void		clean_up(t_cleanup *cl, int flag);

//BUILTINS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//MAIN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//minishell.c
int			shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl);

int			sh_envlen(t_env *sh_env);

//UTILS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int			ft_strlen(const char *str);
t_env		*cr_env(char **env);
t_astn		*parser(const char *input);
t_astn		*ast_cmd(const char *input, size_t *index, t_cms c, int *error);

void		*ft_calloc(size_t nmemb, size_t size);
t_env		*find_env(const char *name, t_env *sh_env);
void		ctrl_c(int sig);

void		free_env(t_env *env);
void		print_sh_env(t_env *sh_env);
void		printenvp(char **envp);
void		input_enter(void);

//MESSAGES+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void		not_found(const char *cmd);
void		err_msg(char *msg);

#endif