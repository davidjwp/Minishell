/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/10/13 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
*	creates the COMMAND node which holds every token 
*	of the corresponding command in the input, each token is separated by
*	type instead of separators, so are builtins if detected so each token
*	has it's precise type
*/
t_astn	*ast_cmd(const char *input, size_t *g_ind, t_cms c, int *err)
{
	size_t	l_ind;
	int		nbr;
	int		i;

	i = 0;
	l_ind = 0;
	nbr = nbr_token(input);
	if (!nbr || !init_node(c.node, nbr, c.parent, err))
		return (free(c.node), NULL);
	while (nbr != 0)
	{
		c.node->token[i] = (t_token *)malloc(sizeof(t_token));
		if (c.node->token[i] == NULL)
			return (free_tok(c.node->token, i), free(c.node), *err = 1, NULL);
		c.node->token[i] = get_token(input, &l_ind, c.node->token[i]);
		if (c.node->token[i] == NULL)
			return (free_tok(c.node->token, i), free(c.node), *err = 1, NULL);
		nbr -= 1;
		i++;
	}
	*g_ind += l_ind;
	return (c.node);
}

bool	ast_pipe(const char *in, size_t *g_ind, t_astn *pipe, t_astn *p)
{
	int	error;

	error = 0;
	pipe->left = create_ast(cut_l(in, C_PIPE), g_ind, &error, pipe);
	if (error)
		return (false);
	pipe->token = NULL;
	pipe->type = PIPE;
	pipe->parent = p;
	*g_ind += 1;
	pipe->right = create_ast(cut_r(in, C_PIPE), g_ind, &error, pipe);
	if (error)
		return (false);
	return (true);
}

bool	ast_red(const char *in, size_t *g_ind, t_astn *red, t_astn *p)
{
	int		error;

	error = 0;
	red->left = create_ast(cut_l(in, C_RED), g_ind, &error, red);
	if (error)
		return (false);
	red->token = NULL;
	red->type = get_node_type(in, g_ind);
	red->parent = p;
	red->right = create_ast(cut_r(in, C_RED), g_ind, &error, red);
	if (error)
		return (false);
	return (true);
}

t_astn	*create_ast(const char *input, size_t *g_ind, int *error, t_astn *par)
{
	t_astn	*node;

	node = malloc(sizeof(t_astn));
	if (node == NULL)
		return (*error = 1, err_msg("create ast malloc failed"), NULL);
	if (_pipe(input))
	{
		if (!ast_pipe(input, g_ind, node, par))
			return (*error = 1, NULL);
	}
	else if (_red(input))
	{
		if (!ast_red(input, g_ind, node, par))
			return (*error = 1, NULL);
	}
	else
		node = ast_cmd(input, g_ind, (t_cms){par, node}, error);
	if (*error)
		return ( free((char *)input), NULL);
	if (par == NULL)
		return (node);
	return (free((char *)input), node);
}
