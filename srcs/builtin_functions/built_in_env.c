/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:35:19 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 18:52:14 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/******************************** info **************************************/
//
// env env env env env is done
// env kkkkk and env -hgshfgsdg is done
//
//
/***************************************************************************/

//static void	print_env_list(t_env *fake_env);

int	built_in_env(t_one_token *token, t_env *fake_env)
{
	if (fake_env)
	{
		/******** for multiple env ********/
		while(token && !ft_strcmp(token->str, "env"))
			token = token->next;
		/****** i only need write the code like below ********/
		// i just need write from here
		if (token)/*** i wrote it just give an error when we have option or arguments ***/
		{
			/******** for no option part ******/
			int pointer = char_check(*(token->str), '-');
			if (pointer)//it returns pointer
			{
				ft_putstr_fd("env: (based on the subject No Options) invalid option -- '", STDERR_FILENO);
				ft_putchar_fd(*(++token->str), STDERR_FILENO);
				ft_putendl_fd("'", STDERR_FILENO);
				ft_putendl_fd("Try 'env --help' for more information.", STDERR_FILENO);
				exit_status = 125;
			}
			else/******** for no arguments part ******/
				error_env(token->str, "env");
		}		
		else
		{
			print_env_list(fake_env);
			exit_status = 0;
		}
		//untile here
		
		/************ i dont need to handle like below code **************/
		//from here
		// if (token)
		// {
		// 	char *pointer = ft_strchr(token->str, '!');
		// 	if (pointer)
		// 	{
		// 		printf("pointer %s\n", pointer);
		// 		if(*(++pointer))
		// 		{
		// 			printf("++pointer %s\n", pointer);
		// 			error_event_echo(ft_strchr(token->str, '!'));
		// 		}
		// 		else
		// 		{
		// 			if (ft_strchr(token->str, '='))
		// 			{
		// 				print_env_list(fake_env);
		// 				ft_putendl_fd(token->str, STDIN_FILENO);
		// 				exit_status = 0;
		// 			}
		// 			else
		// 				error_env(token->str, "env");
		// 		}
		// 	}
		// 	else
		// 	{
		// 			if (ft_strchr(token->str, '='))
		// 			{
		// 				print_env_list(fake_env);
		// 				ft_putendl_fd(token->str, STDIN_FILENO);
		// 				exit_status = 0;
		// 			}
		// 			else
		// 				error_env(token->str, "env");
		// 	}
		// }
		// else
		// {
		// 	print_env_list(fake_env);
		// 	exit_status = 0;
		// }
		// untile here
	}
	return (exit_status);
}

void	print_env_list(t_env *fake_env)
{
	t_env	*tmp;

	if (!fake_env)
		exit (1);
	tmp = fake_env;
	
	while (tmp != NULL)
	{
		if (tmp->var_value != NULL)
			printf("%s=%s\n", tmp->var_name, tmp->var_value);
		tmp = tmp->next;
	}
	return ;
}