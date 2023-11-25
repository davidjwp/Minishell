/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msgs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/20 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

void	not_found(const char *cmd)
{
	printf("%s: command not found\n", cmd);
}

void	syntax_error(const char *str, t_cleanup *cl)
{
	printf("minishell: syntax error near unexpected token \'%s\'\n", str);
	cl->status = 2;
}

void	err_msg(char *msg)
{
	printf ("minishell: %s\n", msg);
}