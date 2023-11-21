/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/10/30 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

char	*print_type(int type)
{
	char	*types[14];
	int		num[14];
	int		i;

	i = -1;
	if (type != 0 && !(type % 11))
		return ((char *[7]){"ECHO", "CD", "PWD", "EXPORT", "UNSET", "ENV"\
		, "EXIT"}[(type / 10) - 2]);
	while (++i < 14)
	{
		types[i] = (char *[15]){"WORD", "SEPR", "QUOT", "EXST", "APRD", \
		"HERD", "ARGT", "OPER", "REDL", "VARE", "PIPE", "BUIT", "REDR", \
		"COMD"}[i];
		num[i] = (int [14]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}[i];
	}
	i = 0;
	while (type != num[i])
		i++;
	return (types[i]);
}

void	print_tree(t_astn *node)
{
	int	i;

	i = 0;
	if (node->left != NULL)
		print_tree(node->left);
	if (node->right != NULL)
		print_tree(node->right);
	if (node->type != COMD)
		printf ("_________\nnode %s %p\nleft %p\nright %p\ntoken %p\nparent %p\n"\
		, print_type(node->type), node, node->left, node->right, \
		node->token, node->parent);
	else
	{
		printf ("_________\nnode %s %p\nleft %p\nright %p\ntoken %p\nparent %p\n" \
		, print_type(node->type), node, node->left, node->right, node->token, \
		node->parent);
		while (node->token[i] != NULL)
		{
			printf("%s %li %s\n", node->token[i]->content, node->token[i]->len \
			, print_type(node->token[i]->type));
			i++;
		}
	}
}

// bool	parser_rules(t_astn *tree)
// {

// }

t_astn	*parser(const char *input)
{
	t_astn		*tree;
	int			error;
	size_t		g_ind;

	error = 0;
	g_ind = 0;
	tree = create_ast(input, &g_ind, &error, NULL);
	if (error)
		return (NULL);
	// if (!parser_rules(tree))
	// 	return (NULL);
	return (tree);
}

	/*parsing rules here*/
	//no > > so tree->right->left->token[0] == NULL or tree->right->left == 
	// NULL if tree->right->type == REDR
	//no < < 
	//you can have multiple files in those redirections but only the 
	// first one will be redirected
	//check file permissions for redirections, so 