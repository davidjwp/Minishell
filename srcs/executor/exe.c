/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/10 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

/*
*	exe contains the following functions :
*	open_file(), sh_red(), sh_pipe(), clean_up(), execute()
*/
//checks for access permissions and viability of files then opens
int	open_file(t_astn *tree, t_red *_red, int flag)
{
	if (flag != O_APPEND)
	{
		if (access(tree->right->token[0]->content, W_OK) == -1)
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC | O_CREAT, 0644);
		else
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC, 0644);
	}
	else
	{
		if (access(tree->right->token[0]->content, W_OK) == -1)
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC | O_CREAT | O_APPEND, 0644);
		else
			_red->out = open(tree->right->token[0]->content, O_RDWR | \
			__O_CLOEXEC | O_APPEND, 0644);
	}
	if (_red->out == -1)
		return (0);
	return (1);
}

//if the right side of '>' isn't a file or isn't found the parser will catch it
//so this might not even be needed
//there could be case where it is a folder or something else be careful
int	sh_red(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_red	_red;

	if (tree->type == REDL)
	{
		_red.in = open(tree->right->token[0]->content, O_RDONLY | __O_CLOEXEC);
		if (_red.in == -1)
			return (0);
		dup2(_red.in, STDIN_FILENO);
		close(_red.in);
	}
	else if (tree->type == REDR)
	{
		if (!open_file(tree, &_red, 0))
			return (err_msg("open file fail"), 0);
		dup2(_red.out, STDOUT_FILENO);
		close(_red.out);
	}
	else
	{
		if (open_file(tree, &_red, O_APPEND))
			return (err_msg("open file fail"), 0);
		dup2(_red.out, STDOUT_FILENO);
		close(_red.out);
	}
	return (shell_loop(tree->left, sh_env, cl), 1);
}

//creates a pipe by forking in the left then right side of the pipe
int	sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;

	if (pipe(p.pipe_fd) == -1)
		return (err_msg("sh_pipe pipe error"), 0);
	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("sh_pipe fork error"), 0);
	if (!p.l_pid)
	{
		dup2(p.pipe_fd[1], STDOUT_FILENO);
		close_pipe(p.pipe_fd);
		shell_loop(tree->left, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	p.r_pid = fork();
	if (p.r_pid == -1)
		return (err_msg("sh_pipe pipe fork error"), 0);
	if (!p.r_pid)
	{
		dup2(p.pipe_fd[0], STDIN_FILENO);
		close_pipe(p.pipe_fd);
		shell_loop(tree->right, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	return (wait_pipe(p), 0);
}

//cleans up file descriptors the abstract synthax tree and the shell envs
void	clean_up(t_cleanup *cl, int flag)
{
	if (cl->fds != NULL && (flag & CL_FDS))
		close_fds(cl->fds);
	if (cl->tree != NULL && (flag & CL_TRE))
		free_tree(cl->tree);
	if (cl->env != NULL && (flag & CL_ENV))
		free_env(cl->env);
	if ((flag & CL_INP))
	{
		free(cl->input);
		cl->input = NULL;
	}
	if ((flag & CL_HIS))
		rl_clear_history();
}

//executes the command node, might not need that last freeing
int	execute(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	pid_t	pid;
	t_exe	exe;
	int		status;

	pid = fork();
	if (pid == -1)
		return (err_msg("execute fork fail"), 0);
	if (pid)
		return (wait(&status), 1);
	exe._path = cr_pathname(tree->token[0]->content, find_env("PATH", sh_env));
	if (!exe._path)
		return (clean_up(cl, CL_ALL), exit(EXIT_FAILURE), 0);
	exe._envp = cr_envp(sh_env);
	if (!exe._envp)
		return (free(exe._path), clean_up(cl, CL_ALL), exit(EXIT_FAILURE), 0);
	exe.argv = cr_args(tree->token, exe._path);
	if (!exe.argv)
		return (free_split(exe._envp), free(exe._path), clean_up(cl, CL_ALL), \
		exit(EXIT_FAILURE), 0);
	execve(exe._path, exe.argv, exe._envp);
	return (exit(EXIT_FAILURE), 0);
}
