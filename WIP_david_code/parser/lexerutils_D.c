/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:26:11 by djacobs           #+#    #+#             */
/*   Updated: 2023/10/16 17:27:11 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
*	lexerutils_D contains the following functions :
*	
*/
int	init_node(t_astn *node, int nbr, t_astn *p, int *error)
{
	if (!nbr)
		return (0);
	node->type = COMD;
	node->token = (t_token **)malloc(sizeof(t_token) * (nbr + 1));
	if (node->token == NULL)
		return (free(node), *error = 1, err_msg("init alloc fail"), 0);
	node->token[nbr] = NULL;
	node->left = NULL;
	node->right = NULL;
	node->parent = p;
	return (1);
}