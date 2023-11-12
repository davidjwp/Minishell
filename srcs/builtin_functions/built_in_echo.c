/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:34:08 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/04 18:02:37 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/***************************** to verify *************************************/
//
// SYNTAX ERROR???????????  like >>echo>> or echo > <
// echo \n hghg   -----> n hghg
// echo "-n" hol
// ""''echo hola""'''' que""'' tal""''
// echo $HOME \$HOME do i have to handle \ here?
// echo $?HHH$?KKKK? i didn't verify it
// echo $USER
// echo $?KKKK i verified it
// echo $? i need to verify it? (print echo)
// echo [$HOME] how about this?
// echo $LESS$VAR how abourt this?
// echo jhf$kjkjgh$!!!!?????
// echo "" it prints \n
//
/*****************************************************************************/

static void	print_echo(t_one_token *one_cmd);
static int	check_n_str(char *str, char c);
static int	if_n_option(t_one_token *one_cmd);

int  built_in_echo(t_one_token *token)
{
	int	n_flag;

	n_flag = 0;
	if (token && !token->next)//only echo cmd
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		return (exit_status = 0);//return exit_status
	}
	token = token->next;// we pass to the second node
	while (token)
	{
		if (if_n_option(token))// checking -n 
		{
			n_flag = 1;
			token = token->next;
		}
		else
			break ;
	}
	print_echo(token);//im in the next node to print
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return exit_status;
}

static int	if_n_option(t_one_token *one_cmd)
{
	if (one_cmd->str[0] != '-')
		return (0);
	if (check_n_str(&one_cmd->str[1], 'n'))
		return (1);
	return (0);
}

static int	check_n_str(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;//we skip all of the n
	}
	return (1);
}
static void	print_echo(t_one_token *one_cmd)
{
	/******** i only need to write the below loop *******/
	// while (one_cmd)
	// 		{
	// 			ft_putstr_fd(one_cmd->str, 1);
	// 			if (one_cmd->next != NULL)
	// 				ft_putchar_fd(' ', 1);
	// 			one_cmd = one_cmd->next;
	// 		}
	// 	}
	// 	exit_status = 0;
	
	/**** i wrote this below code for checking exit_status just for my program ****/
	if (one_cmd)
	{
		char *str = one_cmd->str;
		if (*str == '$')// print echo $?
		{
			if (*(++str) == '?')
			{
				char *status = ft_itoa(exit_status);
				ft_putstr_fd(status, STDIN_FILENO);
				ft_putstr_fd(++str, STDIN_FILENO);
				free(status);
			}
			else
				ft_putstr_fd(--str, STDIN_FILENO);
		}
		else
		{
			while (one_cmd)
			{
				ft_putstr_fd(one_cmd->str, 1);
				if (one_cmd->next != NULL)
					ft_putchar_fd(' ', 1);
				one_cmd = one_cmd->next;
			}
		}
		exit_status = 0;
	}
}

/************* i tried to handel $variable ?mark and ... ****************/
// static void	print_echo(t_one_token *one_cmd, t_env *fake_env)
// {
// 	char *next_str;
// 	while (one_cmd)
// 	{
// 		//int i = 0; 
// 		//int j = 0;
// 		char *str = one_cmd->str;
// 		//int length = ft_strlen(str);
//		char *pointer = ft_strchr(str, '!');
// 		if (pointer)
//		{
//		 	if(++pointre)
//		 		error_event_echo(ft_strchr(str, '!'));
//		 	else
//				ft_putstr_fd(str, 1);
//		}
// 		else
// 		{
// 			// if (*str == '$')// print echo $?
// 			// {
// 			// 	//printf("*str is %c\n", *str);
// 			// 	if (*(++str) == '?')
// 			// 	{
// 			// 		//printf("*str++ is %c\n", *str);
// 			// 		char *status = ft_itoa(exit_status);
// 			// 		/* printf("int g_status = %d\n", g_status);
// 			// 		printf("str g_status = %s\n", g); */
// 			// 		ft_putstr_fd(status, STDIN_FILENO);
// 			// 		ft_putstr_fd(++str, STDIN_FILENO);
// 			// 	}
// 			// }
// 			// for (i = 0; i < length -1; i++) 
// 			// {
// 			// 	if (str[i] == '$' && str[i + 1] == '?')
// 			// 	{
// 			// 		str[i] = '0'; // instead i have to print exit_status
// 			// 		for (j = i + 1; j < length; j++)
// 			// 			str[j] = str[j + 1];
// 			// 		length--;
// 			// 	}
// 			// }
// 			//printf("i'm here\n");
// 			if (*str != '$')
// 			{
// 				next_str = get_next_str(str, '$');
// 				// printf("\nnext_str %s\n", next_str);
// 				ft_putstr(str);
// 				ft_dollar(next_str, fake_env);
//     		}
// 			else
// 				ft_dollar(str, fake_env);
// 		}
// 		if (one_cmd->next != NULL)
// 			ft_putchar_fd(' ', 1);
// 		one_cmd = one_cmd->next;
// 	}
// 	exit_status = 0;
//}