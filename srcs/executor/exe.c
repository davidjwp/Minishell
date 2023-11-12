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
void	sh_red(t_astn *tree, t_env *sh_env)
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
	shell_loop(tree->left, sh_env);
}


int	sh_pipe(t_astn *tree, t_env *sh_env)
{
	t_pipe	_pipe;

	if (pipe(_pipe.pipe_fd) == -1)
		return (err_msg("pipe error"), 0);
	_pipe.exe.pid = fork();
	if (_pipe.exe.pid == -1)
		return (err_msg("pipe fork error"), close_pipe(_pipe.pipe_fd), 1);
	if (_pipe.exe.pid == 0)
	{
		dup2(_pipe.pipe_fd[1], STDOUT_FILENO);
		close_pipe(_pipe.pipe_fd);
		shell_loop(tree->left, sh_env);
	}
	else
	{
		dup2(_pipe.pipe_fd[0], STDIN_FILENO);
		close_pipe(_pipe.pipe_fd);
		wait(NULL);
		shell_loop(tree->right, sh_env);
	}
	return (2);
}

//main
int	execute(t_astn *tree, t_env *sh_env)
{
	char	*__path;
	char	**__envp;
	char	**argv;
	t_exe	exe;

	__path = cr_pathname(tree->token[0]->content, find_env("PATH", sh_env));
	if (!__path)
		return (0);
	__envp = cr_envp(sh_env);
	if (!__envp)
		return (free(__path), err_msg("cr_envp malloc fail"), 0);
	argv = cr_args(&tree->token[1], __path);
	if (!argv)
		return (err_msg(""), free_split(__envp), 0);
	return (execve(__path, argv, __envp), 2);
}
