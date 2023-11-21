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

#include "../includes/SH_functs.h"
#include "../includes/SH_structs.h"

void	not_found(const char *cmd)
{
	printf("Command \'%s\' not found\n", cmd);
}

void	err_msg(char *msg)
{
	printf ("\nMinishell: %s\n", msg);
}