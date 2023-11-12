/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:11:04 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 11:17:55 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

char	*find_env_value(char *str, t_env *env)
{
	t_env	*head;

	//printf("env %s\n", env->var_name);
	head = env;
	while (head)
	{
		//printf("head->var_name %s\n",head->var_name );
		if (!ft_strcmp(head->var_name, str))
			return (head->var_value);
		head = head->next;
	}
	return (NULL);
}
/* char	*find_env_value(char *str, t_env *env)
{
	t_env	*head;
	char *s=find_env_var(str, 's');
	head = env;
	while (head)
	{
		if (!ft_strcmp(head->var_name, str))
			return (head->var_value);
		head = head->next;
	}
	return (NULL);
} */
char	*find_env_value_cd(char *str, t_env *env)
{
	t_env	*head;
	
	head = env;
	while (head)
	{
		if (head->var_name != NULL)
		{
			if (ft_strcmp(head->var_name, str) == 0)
				return (head->var_value);// if we have variable i return it's value
			else
				head = head->next;
		}
		else
			head = head->next;
	}
	return (NULL);//we don't have this variable
}

char *create_prompt(char *str, t_env *fake_env)
{
	char *prompt;
	int	len = 0;
	int i = 0;
	fake_env = NULL;
	
	while (str[len])
		len++;
	prompt = (char*)malloc(sizeof(char) * (len + 3));
	if (!prompt)
	{
		printf("Alloc failure\n");
		return NULL;
	}
	while (*str)
	{
		prompt[i] = *str;
		i++;
		str++;
	}
	prompt[i++] = '~';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	return (prompt);
}