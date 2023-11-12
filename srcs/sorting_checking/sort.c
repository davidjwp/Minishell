/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:15:48 by rmohamma          #+#    #+#             */
/*   Updated: 2023/10/30 14:59:12 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

static void	ft_swap(char **a, char **b);

// Custom sorting function for the linked list
t_env	*sort_list(t_env *fake_env)
{
	t_env	*tmp;
	t_env *next_tmp;
	
	tmp = fake_env;
	while (tmp != NULL)
	{
		while (tmp && !tmp->var_name)
			tmp = tmp->next;
		next_tmp = tmp->next;
		while (next_tmp && !next_tmp->var_name)
			next_tmp = next_tmp->next;
		if (next_tmp)
		{
			if ((ft_strcmp(tmp->var_name, next_tmp->var_name)) > 0)
			{
				ft_swap(&tmp->var_name, &next_tmp->var_name);
                ft_swap(&tmp->var_value, &next_tmp->var_value);
				tmp = fake_env;
			}
			else
				tmp = tmp->next;
		}
		else
			break;
	}
	return (fake_env);
}

static void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
