
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/10/13 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"


t_astn	*ast_cmd_node(const char *input, size_t *index, t_cms c, int *err)
{
	size_t	res;
	int		nbr;
	int		i;

	i = 0;
	res = 0;
	nbr = nbr_token(input);
	if (!nbr || !init_node(c.node, nbr, c.parent, err))
		return (NULL);
	while (nbr != 0)
	{
		c.node->token[i] = (t_token *)malloc(sizeof(t_token));
		if (c.node->token[i] == NULL)
			return (free_tok(c.node->token, i), free(c.node), *err = 1, NULL);
		c.node->token[i] = get_token(input, c.node->token[i], &res);
		if (c.node->token[i] == NULL)
			return (free_tok(c.node->token, i), free(c.node), *err = 1, NULL);
		nbr -= 1;
		i++;
	}
	index += res;
	return (free((char *)input), c.node);
}

/*
*	creates the COMMAND node which holds every token 
*	of the corresponding command in the input, each token is separated by
*	type instead of separators, so are builtins if detected so each token
*	has it's precise type
*/
t_astn	*ast_cmd_node(const char *input, size_t *index, t_cms c, int *err)
{
	size_t	res;
	int		nbr;
	int		i;

	i = 0;
	res = 0;
	nbr = nbr_token(input);
	if (!nbr || !init_node(c.node, nbr, c.parent, err))
		return (NULL);
	while (nbr != 0)
	{
		c.node->token[i] = (t_token *)malloc(sizeof(t_token));
		if (c.node->token[i] == NULL)
			return (free_tok(c.node->token, i), free(c.node), *err = 1, NULL);
		c.node->token[i] = get_token(input, index, c.node->token[i], &res);
		if (c.node->token[i] == NULL)
			return (free_tok(c.node->token, i), free(c.node), *err = 1, NULL);
		nbr -= 1;
		i++;
	}
	return (free((char *)input), c.node);
}

bool	_pipe(const char *input)
{
	int	index;
	int	t;

	index = 0;
	while (input[index] != 0)
	{
		t = type(input, index);
		if (t == PIPE)
			return (true);
		index++;
	}
	return (false);
}

bool	_red(const char *input)
{
	int	index;
	int	t;

	index = 0;
	while (input[index] != 0)
	{
		t = type(input, index);
		if (t == REDL || t == REDR || t == APRD)
			return (true);
		else if (t == PIPE)
			return (false);
		index++;
	}
	return (false);
}

//could free input right here but that might cause problems later on
const char *cut_pipe(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (flag == C_LEFT)
		while (input[len] && type(input, len) != PIPE)
			len++;
	else if (flag == C_RIGHT)
		while (input[len] && (type(input, len) != PIPE && \
		(type(input, len) == 0 || type(input, len) % 4 != 0)))
			len++;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (i < len)
	{
		str[i] = input[i];
		i++;
	}
	return (str);
}

const char	*cut_red(const char *input, int flag)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (flag == C_LEFT)
		while (input[len] && (type(input, len) == 0 || \
		type(input, len) % 4 != 0))
			len++;
	else if (flag == C_RIGHT)
		while (input[len] && ((type(input, len) == 0 || type(input, len) \
		% 4 != 0) && type(input, len) != PIPE))//this might be useless
			len++;
	str = malloc(sizeof(char) * (len + 1));
	str[len] = 0;
	while (i < len)
	{
		str[i] = input[i];
		i++;
	}
	return (str);
}

bool	ast_pipe(const char *input, size_t *i, t_astn *pipe, t_astn *p)
{
	int	error;

	error = 0;
	pipe->left = create_ast(cut_pipe(&input[*i], C_LEFT), i, &error, pipe);
	if (error)
		return (false);
	pipe->type = PIPE;
	pipe->parent = p;
	*i += 1;
	pipe->right = create_ast(cut_pipe(&input[*i], C_RIGHT), i, &error, pipe);
	if (error)
		return (false);
	return (true);
}

bool	ast_red(const char *input, size_t *i, t_astn *red, t_astn *p)
{
	int		error;
	size_t	l;

	l = 0;
	error = 0;
	red->left = create_ast(cut_red(&input[*i], C_LEFT), i, &error, red);
	if (error)
		return (false);
	red->type = check_spec(input, &l, i);
	red->parent = p;
	red->right = create_ast(cut_red(&input[*i], C_RIGHT), i, &error, red);
	if (error)
		return (false);//free here too
	return (true);
}

//this implies that you have to allocate input, index will increment so i can't tell when the recursivity will go back(i would have used it)
t_astn	*create_ast(const char *input, size_t *i, int *error, t_astn *p)
{
	t_astn	*currentnode;

	currentnode = malloc(sizeof(t_astn));
	if (currentnode == NULL)
		return (*error = 1, err_msg("create ast malloc failed"), NULL);
	if ((p == NULL && *i) || *error)
		return (free((char *)input), NULL);
	if (_pipe(&input[*i]))
	{
		if (!ast_pipe(input, i, currentnode, p))
			return (*error = 1, NULL);
	}
	else if (_red(&input[*i]))
	{
		if (!ast_red(input, i, currentnode, p))
			return (*error = 1, NULL);
	}
	else
		return (ast_cmd_node(input, i, (t_cms){p, currentnode}, error));
	if (*error)
		return ( free((char *)input), NULL);
	if (p == NULL)
		free((char *)input);
	return (currentnode);
}

int	main(void)
{
	t_astn	*tree;
	const char	input[] = "cat << EOF > file | wc -c | tr -d "" > file2";
	size_t		index = 0;
	int			error = 0;

	tree = create_ast(input, &index, &error, NULL);
	(void)tree;
	//two choices here either free  input everytime and lose input later on
	//or make sure to free cut down input everytime which will add lines 
}

