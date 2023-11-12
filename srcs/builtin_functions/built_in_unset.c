/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:35:05 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/02 13:39:47 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/***************************** to verify ******************************/
//
// in bash for (unset "") or (unset '') we dont have any error
//
/*********************************************************************/

static void	unset_variable(char *cmd_name, char *name, t_env **fake_env);

int	built_in_unset(t_one_token *token, t_env *fake_env)
{
	char *cmd_name;

	cmd_name = token->str;
	token = token->next;
	while (token)// means we have the variable
	{
		unset_variable(cmd_name, token->str, &fake_env);
		token = token->next;
	}
	return (exit_status = 0);
}

static void	unset_variable(char *cmd_name, char *name, t_env **fake_env)
{
	t_env	*tmp;
	t_env	*prev_node;

	tmp = *fake_env;
	prev_node = NULL;
	/**** i dont need to handle if condition part base on the subject ****/
	if (!is_valid_option(cmd_name, name))
		return ;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->var_name))
		{
			if (prev_node)
				prev_node->next = tmp->next;
			else
				prev_node = tmp->next;
			free_env_node(tmp);
		}
		prev_node = tmp;
		tmp = tmp->next;
	}
}

