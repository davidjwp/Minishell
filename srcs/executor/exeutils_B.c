/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_B.c                                      :+:      :+:    :+:   */
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
*	exe_utils_A contains the following functions :
*	type(), _pipe(), _red(), cmp(), check_spec()
*/
//get the amount of environment variable using the shell env
int	sh_envlen(t_env *sh_env)
{
	t_env	*tmp;
	int		len;

	len = 1;
	tmp = sh_env;
	if (sh_env->next == tmp)
		return (1);
	sh_env = sh_env->next;
	while (sh_env != tmp)
	{
		len++;
		sh_env = sh_env->next;
	}
	return (len);
}

void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}

void	close_fds(t_fds *fds)
{
	t_fds	*head;
	t_fds	*tmp;

	head = fds;
	while (fds->next != head)
	{
		tmp = fds;
		fds = fds->next;
		close(tmp->fd);
		free(tmp);
	}
	close(fds->fd);
	free(fds);
}

void	wait_pipe(t_pipe p)
{
	close_pipe(p.pipe_fd);
	waitpid(p.r_pid, NULL, 0);
	waitpid(p.l_pid, NULL, 0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*f;

	tmp = env;
	env = env->next;
	while (env != tmp)
	{
		f = env;
		env = env->next;
		free(f->name);
		free(f->value);
		free(f->cl);
		free(f);
	}
	free(env->name);
	free(env->value);
	free(env->cl);
	free(env);
}