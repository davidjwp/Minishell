/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:58:32 by rmohamma          #+#    #+#             */
/*   Updated: 2023/10/30 14:57:30 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

t_env *create_new_env_node(const char *name, const char *value)
{
	t_env	*new_var;

	new_var = (t_env *)malloc(sizeof(t_env));
	if (new_var == NULL)
	{
		perror("export: malloc failed");
		exit(1);
	}
	new_var->var_name = ft_strdup(name);
	new_var->var_value = ft_strdup(value);
	new_var->exported = 1;
	new_var->next = NULL;
	return (new_var);
}
t_env	*get_last(t_env *env)
{
	t_env	*head;

	if (!env)
		return (NULL);
	head = env;
	while (head->next != NULL)
		head = head->next;
	return (head);
}