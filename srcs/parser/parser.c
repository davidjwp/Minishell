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

bool	parser_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->type == PIPE && !*error)
		pipe_rules(node, error, cl);
	if (node->type == APRD && !*error)
		apr_rules(node, error, cl);
	if (node->type == REDR && !*error)
		redr_rules(node, error, cl);
	if (node->type == REDL && !*error)
		redl_rules(node, error, cl);
	if (node->type == COMD && !*error)
		comd_rules(node->token, error, cl);
	if (node->left != NULL && !*error)
		parser_rules(node->left, error, cl);
	if (node->right != NULL && !*error)
		parser_rules(node->right, error, cl);
	if (*error)
		return (false);
	return (true);
}

char	*expand_exst(t_token *token, int status)//check on that
{
	int		len;
	int		tmp;
	char	*content;

	len = 0;
	tmp = status;
	while (tmp || !++len)
		tmp /= 10;
	free(token->content);
	content = malloc(sizeof(char) * (len + 1));
	tmp = status;
	content[len] = 0;
	while (--len)
	{
		content[len] = (tmp % 10) + 48;
		tmp /= 10;
	}
	content[len] = (tmp % 10) + 48;
	return (content);
}

int	expander(t_astn *node, t_cleanup *cl)
{
	int	i;

	i = 0;
	if (node->left != NULL)
		return (expander(node->left, cl), 0);
	if (node->right != NULL)
		return (expander(node->right, cl), 0);
	while (node->token[i] != NULL)
	{
		if (node->token[i]->type == EXST)
			node->token[i]->content = expand_exst(node->token[i], cl->status);
		i++;
	}
	return (0);
}

/*
*	first i create the tree then i use parser_rules to check for 	
*/
t_astn	*parser(const char *input, t_cleanup *cl)
{
	t_astn		*tree;
	int			error;
	size_t		g_ind;

	error = 0;
	g_ind = 0;
	if (!*input)
		return (NULL);
	if (ft_strlen(input) == 1)
	{
		if (*input == '!')
			return (cl->status = 1, NULL);
		if (*input == ':' || *input == '#')
			return (cl->status = 0, NULL);
	}
	tree = create_ast(input, &g_ind, &error, NULL);
	if (error || tree == NULL)
		return (cl->status = 0, NULL);
	if (!parser_rules(tree, &error, cl))
		return (free_tree(tree), NULL);
	expander(tree, cl);
	return (tree);
}

/*parsing rules here*/
//no > > so tree->right->left->token[0] == NULL or tree->right->left == 
// NULL if tree->right->type == REDR
//no < < 
//you can have multiple files in those redirections but only the 
// first one will be redirected
//check file permissions for redirections, so 