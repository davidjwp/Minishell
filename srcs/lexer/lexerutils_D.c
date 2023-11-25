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

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

/*
*	lexerutils_D contains the following functions :
*	init_node(), cut_r(), cut_l(), free_tree()
*/
//initializes node members
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

//cuts the right side of the input depending on which type
const char	*cut_r(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = cut_len(input, flag);
	if (type(input, len) == 4)//wtf???
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

//cuts the left side of the input depending on which type
const char	*cut_l(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = -1;
	len = cut_len(input, flag);
	str = malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (++i < len)
		str[i] = input[i];
	return (str);
}

//gets the node type for redirections
int	get_node_type(const char *input, size_t *g_ind)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (input[i] && (type(input, i) == 0 || type(input, i) % 4 != 0))
		i++;
	check_spec(&input[i], &n);
	*g_ind += n;
	return (type(input, i));
}

//free tree from root to bottom
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
