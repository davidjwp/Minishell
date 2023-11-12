/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:36:43 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 19:35:12 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

void	error_many_args(char *cmd_name)// cd, exit
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": too many arguments", STDERR_FILENO);
	exit_status = 1;
}

void	error_dir(char *str, char *cmd_name)// cd
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	exit_status = 1;//echo $? -> 1
}
void	error_env(char *str, char *cmd_name)// env
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': based on the subject No Arguments (No such file or directory)", STDERR_FILENO);
	exit_status = 127;
}
void	error_numeric( char *str, char *cmd_name)// exit
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit_status = 2;
}

void error_event(char *pointer)// valid_option export
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(pointer, STDERR_FILENO);
	ft_putendl_fd(": event not found", STDERR_FILENO);
	exit_status = 0;
}

void	ft_id_error(char *str, char *cmd_name)//export
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	exit_status = 1;//echo $? -> 1
}
void	ft_quote_id_error(char *cmd_name)// export
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd("not a valid identifier", STDERR_FILENO);
	exit_status = 1;//echo $? -> 1
}
void	quote_error(void)//export
{
	ft_putendl_fd("bash: missing closing quote", STDERR_FILENO);
	exit_status = 1;
}

void ft_perror_one_cmd(char *cmd_name)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	perror(": ");
	exit_status = 1;//echo $? -> 1
}
void invalid_cmd_error(char *cmd_name)//export
{
	if (*cmd_name)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit_status = 127;//echo $? -> 1
	}
}
void	error_message(char *name)
{
	ft_putstr_fd("bash: unset: `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
	exit_status = 1;
}

void error_invalid_name(char *pointer, char *name, int number)// export
{
	int i = 0;
	
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	while (i < number)
		ft_putchar_fd(pointer[i++], STDERR_FILENO);
	ft_putendl_fd("\': invalid option", STDERR_FILENO);
	exit_status = 2;
}

void error_event_echo(char *pointer)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(pointer, STDERR_FILENO);
	ft_putendl_fd(": event not found", STDERR_FILENO);
	exit_status = 0;
}
void ft_exclamation_error(int i, char *str)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	while (str[i])
		ft_putchar_fd(str[i++], STDERR_FILENO);
	ft_putendl_fd(": event not found", STDERR_FILENO);
	exit_status = 0;//?
}
void error_cmd_notfound(char *pointer)
{
	ft_putstr_fd(++pointer, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit_status = 127;
}