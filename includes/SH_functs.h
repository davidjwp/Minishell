/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SH_functs.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 21:12:56 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/11 21:12:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_FUNCTS_H
# define SH_FUNCTS_H

# include "SH_structs.h"

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
int			nbr_token(const char *input);
void		free_cmd_node(t_astn *cmd);
void		free_tok(t_token **tokens, int last);
char		*get_quote(const char *input, size_t *l_ind, size_t *len);
int			cut_len(const char *input, int flag);

//lexerutils_D
int			init_node(t_astn *node, int nbr, t_astn *p, int *error);
const char	*cut_r(const char *input, int flag);
const char	*cut_l(const char *input, int flag);
int			get_node_type(const char *input, size_t *g_ind);
void		free_tree(t_astn *node);

//create_ast
t_token		*get_token(const char *input, size_t *l_ind, t_token *token);
t_astn		*create_ast(const char *input, size_t *i, int *error, t_astn *p);

//utils
char		**ft_split(const char *s, char c);
void		free_split(char **split);
void		free_node(t_astn *red);

//PARSER+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//parser.c
bool		parser_rules(t_astn *node, int *error, t_cleanup *cl);
char		*expand_exst(t_token *token, int status);
t_astn		*parser(const char *input, t_cleanup *cl);

//parser_A.c
bool		pipe_rules(t_astn *node, int *error, t_cleanup *cl);
bool		apr_rules(t_astn *node, int *error, t_cleanup *cl);
bool		redl_rules(t_astn *node, int *error, t_cleanup *cl);
bool		redr_rules(t_astn *node, int *error, t_cleanup *cl);
bool		comd_rules(t_token **token, int *error, t_cleanup *cl);

//parser_B.c
int			add_line(t_herd *lines, char *line);
void		free_herd(t_herd *lines);
int			comp_lines(t_herd *lines, char **line);
t_herd		*lines_init(t_astn *node, int pos);
char		*here_doc(t_astn *node, int *error, int pos, t_cleanup *cl);


//parser_C.c
int			gnl(char **line);
int			rem_herd(t_astn *node, int pos);
size_t		ft_strcat(char *dest, const char *src);

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
int			sh_envlen(t_env *sh_env);
void		close_pipe(int *pipe);
void		close_fds(t_fds *fds);
void		wait_pipe(t_pipe p);
void		free_env(t_env *env);


//exe_utils_C
t_env		*find_env(const char *name, t_env *sh_env);
char		*path_cmd(const char *cmd);


void		clean_up(t_cleanup *cl, int flag);

//BUILTINS+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//MAIN+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//minishell.c
int			shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl);

int			sh_envlen(t_env *sh_env);

//UTILS++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//utils_A.c
char		*print_type(int type);
void		print_tree(t_astn *node);
int			ft_strlen(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
void		print_sh_env(t_env *sh_env);

//utils_B.c
void		input_enter(void);
int			get_fd(int stdio, t_fds *fds);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

//utils_C.c
int			gnl(char **line);

t_env		*cr_env(char **env);
t_astn		*parser(const char *input, t_cleanup *cl);
t_astn		*ast_cmd(const char *input, size_t *index, t_cms c, int *error);
void		ctrl_c(int sig);

void		free_env(t_env *env);
void		printenvp(char **envp);

//fds.c
int			fd_redirection(void *type, int redpipe, t_cleanup *cl);
bool		res_fd(int type, t_cleanup *cl);
void		rem_fd(t_fds *fd_lst, int fd);
int			add_fd(t_fds *fd_lst, int fd);
t_fds		*init_fds(void);

//MESSAGES+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void		syntax_error(const char *str, t_cleanup *cl);
void		not_found(const char *cmd);
void		err_msg(char *msg);

#endif