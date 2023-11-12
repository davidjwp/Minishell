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

//find the shell environment variable by name
t_env	*find_env(const char *name, t_env *sh_env)
{
	t_env	*tmp;

	tmp = sh_env;
	if (sh_env == NULL)
		return (NULL);
	if (cmp(name, sh_env->name) == true)
		return (sh_env);
	sh_env = sh_env->next;
	while (cmp(name, sh_env->name) != true && sh_env != tmp)
		sh_env = sh_env->next;
	if (sh_env == tmp)
		return (NULL);
	return (sh_env);
}

int	sh_envlen(t_env *sh_env)
{
	t_env	*tmp;
	int		len;

	len = 1;
	tmp = sh_env;
	if (sh_env == NULL)
		return (4);
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