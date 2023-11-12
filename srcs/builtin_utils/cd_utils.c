/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:16:37 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 11:24:07 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

void	specific_path(t_env *curr_env, char *str)
{
	char	*value;
	int		result;

	value = find_env_value_cd(str, curr_env);
	if (!value)//when we dont have this env's variable
		exit_status = 1;// exit_status = 1 // error
	else
	{
		result = chdir(value);//change the current working directory (0 or -1)
		if (result)//-1 when we dont have a such directory
		{
			error_dir(value, "(specific_path_fun)cd");
			exit_status = 1;// exit_status = 1 // error
		}
		change_path(curr_env);
	}
}
/*** in need this function because in bash unset HOME + cd + pwd we have home adress ***/
void	specific_path_2(t_env *curr_env, t_env *second_env, char *str)
{
	char	*value;
	int		result;

	value = find_env_value_cd(str, second_env);
	if (!value)//when we dont have this env's variable
		exit_status = 1;// exit_status = 1 // error
    else
	{
        result = chdir(value);//change the current working directory (0 or -1)
        if (result)//-1 when we dont have a such directory
        {
            error_dir(value, "(specific_path_2_fun)cd");
            exit_status = 1;// exit_status = 1 // error
        }
	    change_path(curr_env);
    }
}

/*we change the pwd's and oldpwd's value*/
void	change_path(t_env *curr_env)
{
	char	*value;
	t_env	*tmp;

	tmp = curr_env->next;
	while (tmp) /*we find PWD and assigne it's value to the Present Working Directory*/
	{
		if (!ft_strcmp(tmp->var_name, "PWD"))// (Present Working Directory)
		{
			value = ft_strdup(tmp->var_value);
			free(tmp->var_value);//we free the path value and put new value
			tmp->var_value = getcwd(NULL, 0);
			if (tmp->var_value == NULL)
				perror("(change_path_fun)getcwd");
		}
		tmp = tmp->next;
	}
	tmp = curr_env->next;
	while (tmp) /*after we find OLDPWD and change it's variable with PWD's first value*/
	{
		if (!ft_strcmp(tmp->var_name, "OLDPWD"))
		{
			free(tmp->var_value);
			tmp->var_value = value;//we update oldpwd's value
		}
		tmp = tmp->next;
	}
}

void	print_pwd(t_env *curr_env, char *str)
{
	t_env	*curr;

	curr = curr_env;
	while (curr)
	{
		if (!ft_strncmp(curr->var_name, str, ft_strlen(str)))
			printf("%s\n", curr->var_value);
		curr = curr->next;
	}
}