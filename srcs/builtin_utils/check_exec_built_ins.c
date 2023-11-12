/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_built_ins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:29:25 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 13:10:18 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

int	is_built_in(t_one_token *token)
{
	// if (token->type == BUIT)
	// 	return 0;
	int i = 0;
	char	*built_in[] = {"pwd", "cd", "env", "echo", "exit",
		"export", "unset", NULL};

	if (!token)
		return (0);
	while (built_in[i])
	{
		if (!strcmp(built_in[i], token->str))
			return (1);
		i++;
	}
	return (0);
}

//int	exec_built_in(t_one_token *token, t_env *fake_env)
int	exec_built_in(t_one_token *token, t_env *fake_env, t_env *second_env)
{
	int b_status;

	b_status = -42;
	if (!strcmp(token->str, "echo"))
		b_status = built_in_echo(token);
	else if (!strcmp(token->str, "cd"))
	{
		b_status = built_in_cd_edited(token, fake_env, second_env);
		//b_status = built_in_cd(token, fake_env);
		//b_status = built_in_cd(token, fake_env, second_env);//because in bash (cd ~) works with (unset HOME)
	}
	else if (!strcmp(token->str, "pwd"))
	{
		//b_status = built_in_pwd(token);
		b_status = built_in_pwd(token, fake_env);
	}
	else if (!strcmp(token->str, "env"))
		b_status = built_in_env(token, fake_env);
	else if (!strcmp(token->str, "export"))
		b_status = built_in_export(token, fake_env);
	else if (!strcmp(token->str, "unset"))
		b_status = built_in_unset(token, fake_env);
	else if (!strcmp(token->str, "exit"))
		b_status = built_in_exit(token, fake_env);
	return (b_status);
}