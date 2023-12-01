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

void	not_found(char *cmd, int *status)
{
	char	*err;

	err = ft_calloc((ft_strlen(": command not found\n") + ft_strlen(cmd) + \
	ft_strlen("minishell: ") + 1), sizeof(char));
	ft_strcat(err, "minishell: ");
	ft_strcat(err, cmd);
	ft_strcat(err, ": command not found\n");
	write (2, err, ft_strlen(err));
	free(err);
	*status = 127;
}

void	syntax_error(const char *str, t_cleanup *cl)//check that 
{
	char	*err;

	err = ft_calloc((ft_strlen \
	("minishell: syntax error near unexpected token \'") + ft_strlen \
	(str) + ft_strlen("\'\n") + 1), sizeof(char));
	ft_strcat(err, "minishell: syntax error near unexpected token \'");
	ft_strcat(err, str);
	ft_strcat(err, "\'\n");
	perror(err);
	free(err);
	cl->status = 2;
}

void	err_msg(char *msg)
{
	printf ("minishell: %s\n", msg);
}