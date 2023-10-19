
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


/*
*	creates the COMMAND node which holds every token 
*	of the corresponding command in the input, each token is separated by
*	type instead of separators, so are builtins if detected so each token
*	has it's precise type
*/
t_astnode*	ast_cmd_node(const char *input, size_t *index, int nbr, int *error)
{
	t_astnode	*node;
	int			i;

	i = 0;
	if (!nbr)
		return (NULL);
	node = malloc(sizeof(t_astnode));
	if (node == NULL)
		return (*error = 1, err_msg(AST_CN_ERR), NULL);
	if (!init_node(node, nbr, error))
		return (NULL);
	while (nbr != 0)
	{
		node->token[i] = (t_token *)malloc(sizeof(t_token));
		if (node->token[i] == NULL)
			return (free_tokens(node->token, i), free(node), *error = 1, NULL);
		node->token[i] = get_token(input, index, node->token[i]);
		if (node->token[i] == NULL)
			return (free_tokens(node->token, i), free(node), *error = 1, NULL);
		nbr -= 1;
		i++;
	}
	return (free((char *)input), node);
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


// t_astnode	*ast_red(const char *input, t_astnode *red, t_astnode *p)
// {
// 	size_t	i;
// 	int		t;

// 	i = 0;
// 	red->token[0]->len = 0;
// 	t = type (input, i);
// 	while (t != REDL && t != REDR && t != APRD)
// 	{
// 		i++;
// 		t = type (input, i);
// 	}
// 	red->token[0]->content = get_content(input, &i, &red->token[0]->len);
// 	red->type = get_token_type(red->token[0]->content);
// 	red->left = NULL;
// }

//could free input right here but that might cause problems later on
const char	*cut_left_pipe(const char *input)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (type(input, len) != PIPE)
		len++;
	str = malloc(sizeof(char) * (len + 1));//FREE THIS
	str[len] = 0;
	while (i < len)
	{
		str[i] = input[i];
		i++;
	}
	return (str);
}

const char	*cut_right_pipe(const char *input)//wip
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (type(input, len) != PIPE || type(input, len) % 4 != 0)
}

const char	*cut_left_red(const char *input)
{
	char	*str;
	int		len ;
	int		i;

	i = 0;
	len = 0;
	while ((type(input, len) == 0 || type(input, len) % 4))
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

bool	ast_pipe(const char *input, size_t *i, t_astnode *pipe, t_astnode *p)
{
	int	error;

	error = 0;
	pipe->left = create_ast(cut_left_pipe(&input[*i]), i, &error, pipe);
	if (error)
		return (false);
	pipe->type = PIPE;
	pipe->parent = p;
	*i += 1;
	pipe->right = create_ast(cut_right_pipe(&input[*i]), i, &error, pipe);
	if (error)
		return (false);
	return (true);
}

bool	ast_red(const char *input, size_t *i, t_astnode *red, t_astnode *p)
{
	int	error;

	error = 0;
	red->left = create_ast(cut_left_red(&input[*i]), i, &error, red);
	if (error)
		return (false);
	red->type = ;
	return (true);
}

//this implies that you have to allocate input, index will increment so i can't tell when the recursivity will go back(i would have used it)
t_astnode	*create_ast(const char *input, size_t *i, int *error, t_astnode *p)
{
	t_astnode	*currentnode;

	currentnode = malloc(sizeof(t_astnode));
	if (currentnode == NULL)
		return (*error = 1, NULL);
	if ((p == NULL && *i) || *error)
		return (free((char *)input), NULL);
	if (_pipe(&input[*i]))
	{
		if (!ast_pipe(input, i, currentnode, p))
			return (*error = 1, NULL);
		// currentnode->left = create_ast(cut_left_pipe(&input[*i]), i, error, currentnode);
		// currentnode = ast_pipe(currentnode, p);
		// currentnode->right = create_ast(cut_right_pipe(&input[*i]), i, error, currentnode);
	}
	else if (_red(&input[*i]))
	{
		if (!ast_red(input, i, currentnode, p))
			return (*error = 1, NULL);
		currentnode->left = create_ast(cut_left_red(&input[*i]), i, error, currentnode);
		// currentnode = ast_red(input, currentnode, p);
	}
	else
		return (ast_cmd_node(input, i, nbr_token(&input[*i]), error));
	if (*error)
		return ( free((char *)input), NULL);
	 if (p == NULL)
	 	free((char *)input);
	return (currentnode);
}

int	main(void)
{
	t_astnode	*tree;
	const char	input[] = "cat << EOF > file | wc -c | tr -d "" > file2";
	size_t		index = 0;
	int			error = 0;

	tree = create_ast(input, &index, &error, NULL);
	(void)tree;
	//two choices here either free  input everytime and lose input later on
	//or make sure to free cut down input everytime which will add lines 
}

