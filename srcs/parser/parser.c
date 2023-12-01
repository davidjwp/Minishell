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

char	*expand_exst(int status, int *len)
{
	int		tmp;
	char	*exst;
	int		l_len;

	*len = 0;
	tmp = status;
	while (tmp && ++*len)
		tmp /= 10;
	l_len = *len;
	exst = malloc(sizeof(char) * (l_len + 1));
	if (exst == NULL)
		return (NULL);
	tmp = status;
	exst[l_len] = 0;
	while (--l_len)
	{
		exst[l_len] = (tmp % 10) + 48;
		tmp /= 10;
	}
	exst[l_len] = (tmp % 10) + 48;
	return (exst);
}

int	exst_token(char *content, int i, int *error, t_cleanup *cl)
{
	char	*exst;
	char	*new;
	int		len;
	int		in;

	in = -1;
	if (cl->status > 255)
		exst = expand_exst(WEXITSTATUS(cl->status), &len);
	else
		exst = expand_exst(cl->status, &len);
	if (exst == NULL)
		return (*error = 1, 0);
	len = ft_strlen(content) + len - 2;
	new = ft_calloc(len + 1, sizeof(char));
	if (new == NULL)
		return (free(exst), *error = 1, 0);
	while (++in < i)
		new[in] = content[in];
	ft_strcat(new, exst);
	ft_strcat(new, &content[i + 2]);
	free(content);
	return (new);
}

//VAR=$?$USER
//1davidjwp
int	expand_token(t_token *token, int *error, t_cleanup *cl)
{
	size_t	i;

	i = 0;
	while (token->content[i])
	{
		if (type(token->content, i) == EXST)
			token->content = exst_token(token->content, i, error, cl);
		else if (type(token->content, i) == VARE)
			token->content = vare_token(token->content, i, error, cl);//maybe don't because she's already handling this except for vare in quotes
		if (*error)
			return (0);
		i++;
	}
}

int	expander(t_astn *node, int *error, t_cleanup *cl)
{
	int	i;

	i = 0;
	if (node->left != NULL)
		return (expander(node->left, error, cl), 0);
	if (node->right != NULL)
		return (expander(node->right, error, cl), 0);
	if (node->type == COMD)
	{
		while (node->token[i] != NULL)
		{
			if (!expand_token(node->token[i], error, cl))
				return (0);
			i++;
		}
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
	if (tree != NULL)
		return (print_tree(tree), tree); 
	if (error || tree == NULL)
		return (NULL);
	if (!parser_rules(tree, &error, cl))
		return (free_tree(tree), NULL);
	if (!expander(tree, &error, cl))
		return (free_tree(tree), NULL);
	return (tree);
}

/*parsing rules here*/
//no > > so tree->right->left->token[0] == NULL or tree->right->left == 
// NULL if tree->right->type == REDR
//no < < 
//you can have multiple files in those redirections but only the 
// first one will be redirected
//check file permissions for redirections, so 