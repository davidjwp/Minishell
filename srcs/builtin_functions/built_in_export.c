/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:35:14 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 19:43:07 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/********************************** to verify ********************************/
// export $HOME.
// export PPP="fgdfg fdggd" does not work because of my split.
// export "" with it's error > done export "   llll" (in my cod my tokenization
// is not correct).
// in correct parsing it has to work with export $? my code it gives correct 
// error like bash but it has to replace $? with exit_status.
//
// i have to verify (export HOLA=bonjour=casse-toi + echo $HOLA) i dont know 
// with correct parsing my program will work or not
// 
//
/*****************************************************************************/

static int export_variable(t_one_token *token, t_env *env);
static char *get_token_value(const char *var, char c);
static void add_env_var_if_find(t_env *env, char *variable, char *value);
static void add_env_var(t_env **env, const char *variable, const char *value);

int built_in_export(t_one_token *token, t_env *fake_env)
{
	int b_status;

	b_status = 0;
	// print_environment_variables(sorted_env);
	if (token && (token->next == NULL))// only export command
	{
		print_exported_env(fake_env);
		return exit_status;
	}
	if (token->next && !is_valid_option(token->str, token->next->str))
		return (exit_status);
	token = token->next; // we pass to the new variable which we wanna to add to the env
	while (token)
	{
		b_status = export_variable(token, fake_env);
		token = token->next;
	}
	return (b_status);
}

static int export_variable(t_one_token *token, t_env *env)
{
	char *var;
	char *value;

	value = NULL;
	//printf("str is: %s\n", token->str);
	if (!is_valid_identi(token->str))
		return (exit_status);
	else if (ft_strchr(token->str, '=')) // there is =
	{
		var = token->str;
		value = get_token_value(var, '=');
		if (value)
			add_env_var_if_find(env, var, value);
		else
		{
			ft_id_error(token->str, "export");
			return (exit_status);
		}
	}
	else if (!ft_strchr(token->str, '='))// there is not =
	{
		/*******export $HOME and export $hhghgh*/
		if (*token->str == '$')//*************** do i have to handle $
		{
			token->str++;
			char *value = find_env_value(token->str, env);
			if (value)
				ft_id_error(value, "export");
			else
				print_exported_env(env);
			return (exit_status);
		}
		var = token->str;
		//printf("im here \n");
		if (!value)//our value is NULL
			add_env_var_if_find(env, var, value);
	}
	else
		find_exported(env, token->str);
	return (0);
}

static char *get_token_value(const char *var, char c)
{
	char *value;

	value = ft_strchr(var, c);//it returns a pointer to the place of =
	if (value)
	{
		*value = '\0';//we replace = with \0
		value++;//we have just value
	}
	return (value);
}

static void add_env_var_if_find(t_env *env, char *variable, char *value)
{
	add_env_var(&env, variable, value);
	find_exported(env, variable);
}

static void add_env_var(t_env **env, const char *variable, const char *value)
{
	t_env *env_var;
	t_env *new_node;
	t_env *last_node;
	//const char *tmp = value;
	
	/********* i handle this for my program **********/
	if (ft_strchr(value, ';'))//export X=$hhh;gg > gg: command not found
	{
		char *p = ft_strchr(value, ';');
		invalid_cmd_error(++p);
		return;
	}
	env_var = find_env_var(*env, variable);
	if (env_var) // we find variable in the env
	{
		free(env_var->var_value);
		env_var->var_value = ft_strdup(value);
	}
	else // we dont find var
	{/*************************do i solve ! and ;*************************/
		// char *pointer;
		// pointer = ft_strchr(tmp, ';');
		// if (pointer)//export X=$hhh;gg > gg: command not found
		// {
		// 	printf("value %s and pointer %s\n", tmp, pointer);
		// 	invalid_cmd_error(pointer);
		// 	return;
		// }
		// else
		// {
		// 	pointer = ft_strchr(value, '!');//export X=$hhh!gg > !gg: event not found
		// 	if (pointer)
		// 	{
		// 		printf("value %s and pointer %s\n", value, pointer);
		// 		ft_putstr_fd("bash: !", STDERR_FILENO);
		// 		ft_putstr_fd(pointer, STDERR_FILENO);
		// 		ft_putendl_fd(": event not found", STDERR_FILENO);
		// 		return ;
		// 	}
		// }
		new_node = create_new_env_node(variable, value);
		if (*env == NULL)
			*env = new_node;
		else
		{
			last_node = get_last(*env);
			last_node->next = new_node;
		}
	}
}