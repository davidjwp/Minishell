
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
		return (NULL);
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
	return (free((char *)input), c.node);
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

bool	ast_pipe(const char *in, size_t *g_ind, t_astn *pipe, t_astn *p)
{
	int	error;

	error = 0;
	pipe->left = create_ast(cut_l(in, C_PIPE), g_ind, &error, pipe);
	if (error)
		return (false);
	pipe->type = PIPE;
	pipe->parent = p;
	*g_ind += 1;
	pipe->right = create_ast(cut_r(in, C_PIPE), g_ind, &error, pipe);
	if (error)
		return (false);
	return (true);
}

int	get_node_type(const char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && (type(input, i) == 0 || type(input, i) % 4 != 0))
		i++;
	return (type(input, i));
}

bool	ast_red(const char *in, size_t *g_ind, t_astn *red, t_astn *p)
{
	int		error;

	error = 0;
	red->left = create_ast(cut_l(in, C_RED), g_ind, &error, red);
	if (error)
		return (false);
	red->type = get_node_type(in);
	check_spec(in, g_ind);
	red->parent = p;
	red->right = create_ast(cut_r(in, C_RED), g_ind, &error, red);
	if (error)
		return (false);//free here too
	return (true);
}

//you might not need to cut input at all and only use global index

//this implies that you have to allocate input, index will increment so i can't tell when the recursivity will go back(i would have used it)
t_astn	*create_ast(const char *input, size_t *g_ind, int *error, t_astn *par)
{
	t_astn	*node;

	node = malloc(sizeof(t_astn));
	if (node == NULL)
		return (*error = 1, err_msg("create ast malloc failed"), NULL);
	if ((par == NULL && *g_ind) || *error)
		return (free((char *)input), NULL);
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
		return (ast_cmd(input, g_ind, (t_cms){par, node}, error));
	if (*error)
		return ( free((char *)input), NULL);
	if (par == NULL)//might not need that 
		return (node);
	return (free((char *)input), node);
}

int	main(void)
{
	t_astn		*tree;
	size_t		index = 0;
	const char	input[] = "cat << EOF > file | wc -c | tr -d "" > file2";
	int			error = 0;

	tree = create_ast(input, &index, &error, NULL);
	(void)tree;
	//two choices here either free  input everytime and lose input later on
	//or make sure to free cut down input everytime which will add lines 
}

