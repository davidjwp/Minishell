/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:34:27 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 12:17:47 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/******************************** to verify **********************************/
//
// i have to verify all the free
//
/*****************************************************************************/

static void exit_exec(t_one_token *token, t_env *fake_env);
static int is_all_digit(char *str);
static void ft_exit_status(t_one_token *token, t_env *fake_env);
static long long	ft_atoi_max(char *str);

int built_in_exit(t_one_token *token, t_env *fake_env)
{
	if (token->next == NULL)// we have just exit command
		exit_exec(token, fake_env); // exit_status = 0;
	else
	{
		if (!is_all_digit(token->next->str))// it's not digit// numeric argument required
			exit_exec(token, fake_env);// exit_status = 2;
		else// it is digit
		{
			if (token->next->next == NULL)// we have just one digit arg after exit cmd
				ft_exit_status(token, fake_env);// exit_status = token->next->str;
			else// we have more than one argument
			{
				ft_putendl_fd("exit", STDERR_FILENO);// it does not exit fronm the bash
				error_many_args(token->str); // exit_status = 1;
			}
		}
	}
	return (exit_status);
}

static void exit_exec(t_one_token *token, t_env *fake_env)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (token->next && !is_all_digit(token->next->str))// it's not digit
		error_numeric(token->next->str, token->str);// numeric argument required
	else
		exit_status = 0;
	free_all(token, fake_env);
	exit(exit_status);
}

static void ft_exit_status(t_one_token *token, t_env *fake_env)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit_status = ft_atoi_max(token->next->str);
	free_all(token, fake_env);
	exit(exit_status);
}

static int is_all_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-') // exit -66666 6666
			i++;
		if (!ft_isdigit(str[i])) // it's not digit
			return (0);
		++i;
	}
	return (1);
}
static long long	ft_atoi_max(char *str)
{
	int					neg;
	int					i;
	unsigned long long res;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = (res * 10) + (str[i++] - '0');
		if (res >  LLONG_MAX || (res > (LLONG_MAX) && neg == -1))
		{
			error_numeric(str, "exit");
			return exit_status;
			// return (ft_printf("bash: exit: %s: numeric argument required\n", str),
			// 	2);
		}
	}
	return ((long long)res * neg);
}
