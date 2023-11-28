/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_A.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/23 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

bool	pipe_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL || node->left == NULL)
		return (*error += 1, syntax_error("|", cl), false);
	return (true);
}

bool	apr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	if (node->right->type == APRD)
		return (*error += 1, syntax_error(">>", cl), false);
	return (true);
}

bool	redr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->left == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	return (true);
}

bool	redl_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->left != NULL)
		return (comd_rules(node->left->token, error, cl));
	if (node->right != NULL)
		return (comd_rules(node->right->token, error, cl));
	if (node->left == NULL || node->right == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	return (true);
}

bool	comd_rules(t_token **token, int *error, t_cleanup *cl)
{
	size_t	y;
	int		i;

	i = 0;
	y = 0;
	while (token[i] != NULL)
	{
		while (token[i]->content[y])
		{
			if (type(token[i]->content, y) == HERD && token[i + 1] == NULL)
				return (*error += 1, syntax_error("newline", cl), false);
			y++;
		}
		y = 0;
		i++;
	}
	return (true);
}
