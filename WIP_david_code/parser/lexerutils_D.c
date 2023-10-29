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

const char	*cut_r(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (flag == C_PIPE)
		while (input[len] && type(input, len) != PIPE)
			len++;
	else if (flag == C_RED)
		while (input[len] && (type(input, len) == 0 || \
		type(input, len) % 4 != 0))
			len++;		
	while (input[++len])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	str[i] = 0;
	len -= i;
	i = -1;
	while (input[len] != 0)
		str[++i] = input[len++];
	return (str);
}

const char	*cut_l(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = -1;
	len = 0;
	if (flag == C_PIPE)
		while (input[len] && type(input, len) != PIPE)
			len++;
	else if (flag == C_RED)
		while (input[len] && (type(input, len) == 0 || \
		type(input, len) % 4 != 0))
			len++;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (++i < len)
		str[i] = input[i];
	return (str);
}

void	free_tree(t_astn *node)
{
	if (node->left != NULL)
		free_tree(node->left);
	if (node->right != NULL)
		free_tree(node->right);
	if (node->type == COMD)
		free_cmd_node(node);
	else
		free(node);
}
