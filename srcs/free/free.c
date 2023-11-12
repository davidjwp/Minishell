/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:45:42 by rmohamma          #+#    #+#             */
/*   Updated: 2023/10/30 14:58:01 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

void	free_double_pointer(char **array)
{
	int i = 0;
	
	while(array[i])
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free(array);
	array = NULL;
}

void	free_token(t_one_token *token)
{
	t_one_token *current = token;
    while (current != NULL)
	{
        t_one_token *temp = current;
        current = current->next;
        free(temp->str);
        free(temp);
    }
}
void free_env(t_env *envList)
{
	t_env *current = envList;
    while (current != NULL) {
        t_env *temp = current;
        current = current->next;
        free(temp->var_name);
        free(temp->var_value);
        free(temp);
    }
}

void	free_env_node(t_env *head)
{
	if (head == NULL)
		return ;
	/* printf("(for free_node )head->exported is %d \n", head->exported);
	printf("(for free_node )head->var_name is %s \n", head->var_name); */
	
	if (head->exported != 0)
	{
		if (head->var_name && head->var_value)
		{
			free(head->var_name);
			head->var_name = NULL;
			free(head->var_value);
			head->var_value = NULL;
			/* free(head->str);
			head->str = NULL; */
		}
		else if (head->var_name && !head->var_value)
		{
			free(head->var_name);
			head->var_name = NULL;
		}
		/*free(head);//vaghti ino minevisam error mide
		head = NULL;*/
	}
}

void	free_all(t_one_token *token, t_env *fake_env)
{
	if (!fake_env)
		free_env(fake_env);
	if (!token)
		free_token(token);
	//free_n_close_heredoc(&data->here_doc, 0);
}