
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:48:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/10/09 23:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Minishell.h"

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
		else if (t == REDL || t == REDR || t == APRD)
			return (false);
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

bool	_cmd(const char *input)
{
	int	index;
	int	t;

	index = 0;
	while (input[index] != 0)
	{
		t = type(input, index);
		if (t == APRD || t == REDL || t == REDR || t == PIPE)
			return (false);
		index++;
	}
	return (true);
}


t_astnode	*ast_red(const char *input, size_t *i, t_astnode *n, int *error)
{
	n = malloc(sizeof(t_astnode));

	n->token[0] = get_token(input, i, n->token[0]);
	if (n->token[0] == NULL)
		return (*error = 1, NULL);
	
}

t_astnode	*ast_pipe(const char *input, size_t *i, t_astnode *n, int *error)
{
	n = malloc(sizeof(t_astnode));
	
	n->token[0] = get_token(input, i, n->token[0]);
}

t_astnode	*create_ast(const char *input, size_t *i, int *error, t_astnode *node)
{
	t_astnode	*current;

	if (*error || node == NULL)
		return (NULL);
	if (_pipe(&input[*i]))
	{
		current->left = node;
		current = create_ast(input, i, error, ast_cmd_node(input, i, \
		nbr_token(&input[*i]), error));
		current->type = PIPE;
	}
	else if (_red(&input[*i]))
	{
		current->left = node;
		current = create_ast(input, i, error, ast_cmd_node(input, i, \
		nbr_token(&input[*i]), error));
		return (ast_red(input, i, current, error));
	}
	else if (_cmd(&input[*i]))
		return (node);
	if (*error)
		return (NULL);
}

int	main(void)
{
	t_astnode	*tree;
	const char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	size_t		index = 0;
	int			error = 0;

	tree = create_ast(input, &index, &error, ast_cmd_node(input, &index, \
	nbr_token(&input[index]), &error))
	
	
	;
}


// t_astnode	*ast_red(const char *input, size_t *i, int *error)
// {
// 	t_astnode	*node;
// 	size_t		len;

// 	len = 0;
// 	node = malloc(sizeof(t_astnode));
// 	node->left = ast_cmd_node(input, i, nbr_token(&input[*i]), error);
// 	if (*error)
// 		return (NULL);
// 	node->type = type(input, *i);
// 	it_token(input, &len, i, IT_TOK);
// 	len = 0;
// 	it_token(input, &len, i, IT_SEP);
// 	if (type(input, *i) == PIPE)
// 		ast_pipe(input, i, error); 
	
// }

// t_astnode	*ast_pipe(const char *input, size_t *i, int *error)
// {
// 	t_astnode	*left;
	
// 	left = ast_red(input, i, error);
// }

// t_astnode	*create_ast(const char *input, size_t *i, int *error, t_astnode *node)
// {
// 	t_astnode	*left;
	
// 	left = ast_pipe(input, i, error);
// }

// int	main(void)
// {
// 	t_astnode	*tree;
// 	const char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
// 	size_t		index = 0;
// 	int			error = 0;

// 	tree = create_ast(input, &index, &error, NULL);

// }

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

bool	_cmd(const char *input)
{
	int	index;
	int	t;

	index = 0;
	while (input[index] != 0)
	{
		t = type(input, index);
		if (t == APRD || t == REDL || t == REDR || t == PIPE)
			return (false);
		index++;
	}
	return (true);
}


t_astnode	*ast_red(const char *input, size_t *i, t_astnode *n, int *error)
{
	n = malloc(sizeof(t_astnode));

	n->token[0] = get_token(input, i, n->token[0]);
	if (n->token[0] == NULL)
		return (*error = 1, NULL);
	
}

t_astnode	*ast_pipe(const char *input, size_t *i, t_astnode *n, int *error)
{
	n = malloc(sizeof(t_astnode));
	
	n->token[0] = get_token(input, i, n->token[0]);
}

t_astnode	*left_pipe(const char *input, size_t *i, int *error)
{
	
}


t_astnode	*create_ast(const char *input, size_t *i, int *error, t_astnode *node)
{
	t_astnode	*current;

	if (*error || (node == NULL && *i))
		return (NULL);
	if (_pipe(&input[*i]))
	{
		current = create_ast(input, i, error, left_pipe(input, i, \
		nbr_token(&input[*i]), error));
		current->type = PIPE;
	}
	else if (_red(&input[*i]))
	{
		current->left = node;
		current = create_ast(input, i, error, ast_cmd_node(input, i, \
		nbr_token(&input[*i]), error));
		return (ast_red(input, i, current, error));
	}
	else if (_cmd(&input[*i]))
		return (node);
	if (*error)
		return (NULL);
}

int	main(void)
{
	t_astnode	*tree;
	const char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	size_t		index = 0;
	int			error = 0;

	tree = create_ast(input, &index, &error, NULL);
}

/*

t_astnode	*ast_pipe(int *error, t_astnode *p)
{
	t_astnode	*pipe;

	pipe = malloc(sizeof(t_astnode));
	if (pipe == NULL)
		return (*error = 1, NULL);
	pipe->token[0]->content = NULL;
	pipe->type = PIPE;
	pipe->parent = p;
	pipe->left = NULL;
	pipe->right = NULL;
	return (pipe);
}

t_astnode	*ast_red(const char *input, size_t *i, int *error, t_astnode *p)
{


}

const char	*cut_left_pipe(const char *input)
{
	char	*str;
	size_t	len;

	len = 0;
	while (type(input, len) != PIPE)
		len++;
	str = malloc(sizeof(char) * (len + 1));//FREE THIS
	str[len] = 0;
	t = -1;
	while (t++ < len)
		str[t] = input[t];
	return (str);
}
//whatever free all that shit figure it out 
void	currentnode(t_astnode *node)
{
	if (node == NULL)
		return (free(node->left));
}

t_astnode	*create_ast(const char *input, size_t *i, int *error, t_astnode *p)
{
	t_asnode	*currentnode;

	currentnode = malloc(sizeof(t_astnode));
	if ((node == NULL && *i) || *error)
		return (free(input), NULL);
	if (_pipe(&input(*i)))
	{
		currentnode->left = create_ast(cut_left_pipe(&input[*i]), i, error, currentnode);
		currentnode = ast_pipe(error, p);
		if (*error)
			return (free_node(currentnode), NULL);
	}
	if (_red(&input[*i]))
	{
		currentnode->left = create_ast(cut_left_red(&input[*i]), i, error, currentnode);
		currentnode->parent = p;

	}
	if (*i)
		free(input);
	return (currentnode);
}

int	main(void)
{
	t_astnode	*tree;
	const char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	size_t		index = 0;
	int			error = 0;

	tree = create_ast(input, &index, &error, NULL);
}

*/