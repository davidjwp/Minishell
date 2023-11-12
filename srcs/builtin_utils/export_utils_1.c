/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:24:04 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 19:08:21 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/********************************* to verify ********************************/
//
//  export HO$?LA=bonjour ($?)
//
//
//
/****************************************************************************/

static int is_valid_id(char *str);

void print_exported_env(t_env *fake_env)
{
	t_env *head;

	if (!fake_env)
		exit(1); //*************or exit (127); it's when we dont have any env
	head = sort_list(fake_env);
	if (!head)
		exit_status = 1;
	else
	{
		while (head != NULL)
		{
			if (head->var_name != NULL)
			{
				if (head->var_value)
					printf("declare -x %s=\"%s\"\n", head->var_name, head->var_value);
				else if (!head->var_value)
					printf("declare -x %s\n", head->var_name);
			}
			head = head->next;
		}
		exit_status = 0;
	}
}

int is_valid_identi(char *str)
{
	size_t i;

	i = 0;
	if(!str[i])//export "" now because of my parsing it does not work but it will be null with correct parsing
	{
		//printf("str %c\n", str[i]);
		ft_quote_id_error("export");
		return 0;
	}
	if (!check_quotes(str))
	{
		quote_error();
		return 0;
	}
	if (char_check(str[i], '=') || ft_isdigit(str[i])) // when '=' or digit is the first char
	{
		ft_id_error(str, "export");
		return (0);
	}
	return (is_valid_id(str));
}

void find_exported(t_env *env, char *var_name)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->var_name) == 0)
		{
			tmp->exported = 1;
			break;
		}
		tmp = tmp->next;
	}
}

t_env *find_env_var(t_env *env, const char *str)
{
	t_env *current;

	if (str == NULL || env == NULL)
		return (NULL);
	current = env;
	while (current)
	{
		if (current->var_name && ft_strcmp(current->var_name, str) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
static int is_valid_id(char *str)
{
	int i;
	
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		if (str[i] == '@' || str[i] == '{' || str[i] == '}' || str[i] == '.' 
		|| str[i] == '-' || str[i] == '?' || str[i] == '+' || str[i] == '*')
		{
			ft_id_error(str, "export");
			return 0;
		}
		// if (str[i] == '!')
		// {
		// 	if (!str[++i])
		// 		ft_id_error(str, "export");
		// 	else
		// 		ft_exclamation_error(--i, str);
		// 	return 0;
		// }
		i++;
	}
	return 1;
}
