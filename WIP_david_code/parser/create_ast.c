
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

t_astnode	*ast_red(const char *input, size_t *i, int *error)
{

}

t_astnode	*ast_pipe(const char *input, size_t *i, int *error)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	
}

t_astnode	*create_ast(const char *input, size_t *i, int *error, t_astnode *node)
{
	t_astnode	*current;

	if (*error || node == NULL)
		return (NULL);
	
	if (_pipe(&input[*i]))
	{
		current = create_ast(input, i, error, ast_cmd_node(input, i, \
		nbr_token(&input[*i]), error));
		current->type = PIPE;
	}
	else if (_red(&input[*i]))
	{
		current = create_ast(input, i, error, ast_red(input, i, error));
		current->type = type(input, *i);
	}
	else
		return (ast_cmd_node(input, i, nbr_token(&input[*i]), error));
	if (*error)
		return (NULL);
}

int	main(void)
{
	t_astnode	*tree;
	const char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	size_t		index = 0;
	int			error = 0;

	create_ast(input, &index, &error, ast_cmd_node(input, &index));
}