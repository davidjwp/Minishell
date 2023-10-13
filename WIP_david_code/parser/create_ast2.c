
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

t_astnode	*ast_pipe(t_astnode *pipe, t_astnode *p)
{
	pipe->token[0]->content = NULL;
	pipe->type = PIPE;
	pipe->parent = p;
	return (pipe);
}

t_astnode	*ast_red(const char *input, size_t *i, int *error, t_astnode *p)
{


}
//could free input right here but that might cause problems later on
const char	*cut_left_pipe(const char *input)
{
	char	*str;
	size_t	len;
	int		i;

	len = 0;
	while (type(input, len) != PIPE)
		len++;
	str = malloc(sizeof(char) * (len + 1));//FREE THIS
	str[len] = 0;
	i = -1;
	while (i++ < len)
		str[i] = input[i];
	return (str);
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
		currentnode->left = create_ast(cut_left_pipe(&input[*i]), i, error, currentnode);
		currentnode = ast_pipe(currentnode, p);//don't forget to SECURE this shit <----^
	}
	if (_red(&input[*i]))
	{
		currentnode->left = create_ast(cut_left_red(&input[*i]), i, error, currentnode);
		currentnode->parent = p;
	}
	if (*error)
		return (free_node(), free((char *)input), NULL);
	 if (p == NULL)
	 	free((char *)input);
	return (currentnode);
}

int	main(void)
{
	t_astnode	*tree;
	const char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	size_t		index = 0;
	int			error = 0;

	tree = create_ast(input, &index, &error, NULL);
	//two choices here either free  input everytime and lose input later on
	//or make sure to free cut down input everytime which will add lines 
}
