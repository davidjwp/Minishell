/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:34:46 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 18:08:26 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SH_functs.h"
#include "../includes/SH_structs.h"

volatile int g_signal;

//this is just to exit the program easier
int	check_input(char *input)
{
	char	*exit = "exit";

	if (!*input)
		return (0);
	for (int i = 0; input[i] != 0; i++)
		if (input[i] != exit[i])
			return (0);
	return (1);
}

//might not need the rl_redisplay function 
int	sh_init(char *input, t_env *sh_env, t_cleanup *cl)
{
	static int	passes;

	// if (!*input)
	// 	return (free(input), 0); 
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	cl->fds = init_fds();
	cl->env = sh_env;
	cl->input = input;
	cl->pids = NULL;
	if (!passes)
		cl->status = 0;
	cl->tree = parser(input, cl);
	passes += 1;
	if (cl->input && *cl->input)
		add_history(cl->input);
	if (cl->tree == NULL)
		return (clean_up(cl, CL_FDS | CL_INP | CL_FDS), 0);
	return (1);
}

void	print_exit(int status)
{
	printf("exit:%d\n", status);
}

/*
* the main function which checks for the availability of the stdio fds
* then the shell env consisting of the env being passed to the main function
* then the main loop 
*/
int	main(int ac, char **av, char **env)
{
	char		*input;
	t_env		*sh_env;
	t_cleanup	*cl;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	sh_env = cr_env(env);
	cl = malloc(sizeof(t_cleanup));
	while (42)
	{
		input = readline(PROMPT);
		if (sh_init(input, sh_env, cl))
		{
			if (check_input(input))
				return (clean_up(cl, CL_ALL), exit(EXIT_SUCCESS), 0);
			shell_loop(cl->tree, sh_env, cl);
		}
		print_exit(cl->status);
	}
	(void)ac, (void)av;
	return (1);
}

// void	exe_builtin(t_astn *tree, int type)
// {
// 	if (type == ECHO)
// 		return (built_in_cd());
// 	else if (type == CD)

// 	else if (type == PWD)

// 	else if (type == EXPORT)

// 	else if (type == UNSET)

// 	else if (type == ENV)

// 	else if (type == EXIT)

// }

bool	is_herd(t_token **token)
{
	int	i;

	i = 0;
	while (token[i]->type == HERD)
	{
		i++;
		if (token[i] == NULL)
			break ;
	}
	if (token[i]->type == HERD)
		return (true);
	return (false);
}

// char	*here_doc(t_astn *node, int *error, int pos, t_cleanup *cl)
// {
// 	t_herd	*lines;
// 	char	*line;
// 	int		lmt_l;

// 	line = NULL;
// 	lines = lines_init(node, pos);
// 	if (lines == NULL)
// 		return (NULL);
// 	if (node->token[pos + 1] == NULL)
// 		return (syntax_error("newline", cl), *error += 1, NULL);
// 	lmt_l = ft_strlen(node->token[pos + 1]->content);
// 	while (gnl(&line))
// 	{
// 		if (ft_strncmp(line, node->token[pos + 1]->content, lmt_l) == 0)
// 			break ;
// 		if (!add_line(lines, line))
// 			return (free_herd(lines), NULL);
// 		free(line);
// 	}
// 	if (!comp_lines(lines, &line))
// 		return (free(line), free_herd(lines), NULL);
// 	return (free_herd(lines), line);
// }

int	exe_herd(t_astn *node, t_env *sh_env, t_cleanup *cl)
{
	// t_pipe	p;
	(void)node;
	(void)sh_env;
	(void)cl;
	return (0);
	// if (pipe(p.pipe_fd) == -1)
	// 	return (err_msg("exe_herd pipe fail"), 0);
	// p.l_pid = fork();
	// if (p.l_pid == -1)
	// 	return (err_msg("exe_herd fork fail"), 0);
	// if (!p.l_pid)
	// {
	// 	fd_redirection(&p, RES_IN | RED_PIP, cl);
	// 	execute(node, sh_env, cl);
	// 	exit(EXIT_SUCCESS);
	// }
	// return (wait(&cl->status), 0);
}

int	sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;

	// write (get_fd(STDO, cl->fds), "entered sh_pipe\n", ft_strlen("entered sh_pipe\n"));
	// if (tree->parent != NULL)
	// 	if (tree->parent->type == PIPE)
	// 		dup2(get_fd(STDI, cl->fds), STDIN_FILENO);
	if (pipe(p.pipe_fd) == -1)
		return (err_msg("sh_pipe pipe error"), 0);
	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("sh_pipe fork error"), 0);
	if (!p.l_pid)
	{
		if (!fd_redirection(&p, RED_PIP | RES_OUT, cl))
			exit(EXIT_FAILURE);
		execute(tree->left, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	wait(&cl->status);
	dup2(p.pipe_fd[0], STDIN_FILENO);
	close_pipe(p.pipe_fd);
	shell_loop(tree->right, sh_env, cl);
	return (dup2(get_fd(STDI, cl->fds), STDIN_FILENO), 0);
}
// write (get_fd(STDO, cl->fds), "HERE\n", ft_strlen("HERE\n"));
// creates a pipe by forking in the left then right side of the pipe
// int	sing_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl)
// {
// 	t_pipe	p;

// 	if (pipe(p.pipe_fd) == -1)
// 		return (err_msg("sh_pipe pipe error"), 0);
// 	p.l_pid = fork();
// 	if (p.l_pid == -1)
// 		return (err_msg("sh_pipe fork error"), 0);
// 	if (!p.l_pid)
// 	{
// 		if (!fd_redirection(&p, RES_OUT | RED_PIP, cl))
// 			exit(EXIT_FAILURE);
// 		shell_loop(tree->left, sh_env, cl);
// 		exit(EXIT_SUCCESS);
// 	}
// 	p.r_pid = fork();
// 	if (p.r_pid == -1)
// 		return (err_msg("sh_pipe pipe fork error"), 0);
// 	if (!p.r_pid)
// 	{
// 		if (!fd_redirection(&p, RES_IN | RED_PIP, cl))
// 			exit(EXIT_FAILURE);
// 		shell_loop(tree->right, sh_env, cl);
// 		exit(EXIT_SUCCESS);
// 	}
// 	return (wait_pipe(p), 0);
// }


/*
* the main shell loop which redirects or pipes the output in order of the tree
* being recursively called
*/
int	shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	if (tree == NULL)
		return (input_enter(), clean_up(cl, CL_FDS | CL_INP), 0);
	if (tree->type == PIPE)
		sh_pipe(tree, sh_env, cl);
	else if (!(tree->type % 4))
		sh_red(tree, sh_env, cl);
	else if (is_herd(tree->token))
		exe_herd(tree, sh_env, cl);
	else
		execute(tree, sh_env, cl);
	if (tree == cl->tree)
		clean_up(cl, CL_FDS | CL_TRE | CL_INP);
	return (1);
}
	// else if (tree->token[0]->type % 11)
	// 	exe_builtin(tree, tree->token[0]->type);
