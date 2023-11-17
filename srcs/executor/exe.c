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
void	open_file(t_astn *tree, t_red *_red, int flag)
{
	if (flag != O_APPEND)
	{
		if (!access(tree->right->token[0]->content, W_OK))
			_red->out = open(tree->right->token[0]->content, O_WRONLY | \
			O_RDONLY | __O_CLOEXEC | O_CREAT);
		else
			_red->out = open(tree->right->token[0]->content, O_WRONLY | \
			O_RDONLY | __O_CLOEXEC);
	}
	else
	{
		if (!access(tree->right->token[0]->content, W_OK))
			_red->out = open(tree->right->token[0]->content, O_WRONLY | \
			O_RDONLY | __O_CLOEXEC | O_CREAT | O_APPEND);
		else
			_red->out = open(tree->right->token[0]->content, O_WRONLY | \
			O_RDONLY | __O_CLOEXEC | O_APPEND);
	}
}

//if the right side of '>' isn't a file or isn't found the parser will catch it
//so this might not even be needed
//there could be case where it is a folder or something else be careful
void	sh_red(t_astn *tree, t_env *sh_env, t_cleanup cl)
{
	t_red	_red;

	if (tree->type == REDL)
	{
		_red.in = open(tree->right->token[0]->content, O_RDONLY | __O_CLOEXEC);
		dup2(_red.in, STDIN_FILENO);
		close(_red.in);
	}
	else if (tree->type == REDR)
	{
		open_file(tree, &_red, 0);
		dup2(_red.out, STDOUT_FILENO);
		close(_red.out);
	}
	else
	{
		open_file(tree, &_red, O_APPEND);
		dup2(_red.out, STDOUT_FILENO);
		close(_red.out);
	}
	shell_loop(tree->left, sh_env, cl);
}

//creates a pipe by forking in the left then right side of the pipe
int	sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup cl)
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
void	clean_up(t_cleanup cl)
{
	if (cl.tree != NULL)
		free_tree(cl.tree);
	if (cl.fds != NULL)
		close_fds(cl.fds);
	if (cl.env != NULL)
		free_env(cl.env);
}

void	printfenv(char **envp)
{
	int		i;
	FILE	*_file;

	i = 0;
	_file = fopen("F_minitest", "rw");
	while (envp[i] != NULL)
	{
		fprintf(_file, "%s\n",envp[i]);
		i++;
	}
}

//executes the command node
int	execute(t_astn *tree, t_env *sh_env, t_cleanup cl)
{
	pid_t	pid;
	t_exe	exe;
	int		status;

	pid = fork();
	if (pid == -1)
		return (err_msg("execute fork fail"), 0);
	if (pid)
		return (wait(&status), 1);
	exe.__path = cr_pathname(tree->token[0]->content, find_env("PATH", sh_env));
	if (!exe.__path)
		return (0);
	exe.__envp = cr_envp(sh_env);
	if (!exe.__envp)
		return (free(exe.__path), err_msg("cr_envp malloc fail"), 0);
	exe.argv = cr_args(tree->token, exe.__path);
	if (!exe.argv)
		return (err_msg(""), free_split(exe.__envp), 0);
	printfenv(exe.__envp);
	execve(exe.__path, exe.argv, exe.__envp);
	return (free(exe.__path), free_split(exe.argv), free_split(exe.__envp), \
	clean_up(cl), 0);
}
