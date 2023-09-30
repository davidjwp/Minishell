`/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:58:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/25 14:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
*	('),(")			QUOTES
*	($)				SPECIAL
*	(>),(<)			OPERATOR
	(>>)			APREDIR
*	(<<)			HEREDOC
*	(|)				PIPE
*	($?)			EXSTAT
*	( ),(\t),(\n)	SEPARATOR
*/

/*
*	create ast creates the symbolic node COMMAND which holds every token 
*	of the corresponding command in the input, each token is separated by
*	type instead of separators, so are builtins if detected so each token
*	has it's precise type
*/
t_astnode*	create_ast_command(char *input, int *index, int	nbr, t_astnode *p)
{
	t_astnode	*newnode;
	int			i;

	i = 0;
	newnode = (t_astnode)malloc(sizeof(t_astnode *));
	if (newnode == NULL)
		return (NULL);
	newnode->type = COMMAND;
	newnode->token = (t_token *)malloc(sizeof(t_token) * (nbr + 1));
	if (newnode->token == NULL)
		return (free(newnode), NULL);
	newnode->token[nbr] = NULL;
	while (nbr != 0)
	{
		newnode->token[i] = (t_token){0, 0, NULL};
		newnode->token[i] = get_token(input, index, newnode->token[i].len);
		if (newnode->token[i] == NULL)
			return (free_tokens(current->token, i), free(newnode), NULL);
		nbr -= 1;
		i++;		
	}
	newnode->parent = p;
	newnode->left = NULL;
	newnode->right = NULL;
	return (newnode);
}

t_astnode*	create_ast_node(char c, t_astnode *left, t_astnode *p, int type)
{
	t_astnode	*newnode;

	newnode = (t_astnode *)malloc(sizeof(t_astnode));
	if (newnode == NULL)
		return (NULL);
	newnode->(*token) = c;
	newnode->type = type;
	newnode->parent = p;
	newnode->left = left
	newnode->right = NULL;
	return (newnode);
}

//recursive descent parser for redirections
t_astnode*	ast_red_node(char *input, int *i, t_astnode *parent)
{
	t_astnode	*current;
	t_astnode	*right;
	t_astnode	*left;

	left = create_ast_command(input, i, nbr_token(&input[*i]), current);
	if (left == NULL)
		return (NULL);
	right = create_ast_command(input, i, nbr_token(&input[*i]), current);
	if (right == NULL)
		return (NULL);
	current = create_ast_node(input[*i], left, parent, type(input[*i]));
	if(current == NULL)
		return (NULL);
	current->left = left;
	if (input_red(&input[i]))
	{
		current->left = left;
	}
	if (left == NULL)
		return (NULL);
}

//recursive descent parser for pipes
t_astnode	*ast_pipe_node(char *input, int *index)
{
	t_astnode	*current;
	t_astnode	*left;

	if (input_red(&input[index]))
		left = ast_red_node(input, index, current);
	if (input_pipe(&input[index]))
	{
		create_ast_pipe(input, index, current);	
	}
	left = parse_secondary(input, index);
	current = left;
	return (current);
}

main(void)
{
	char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	int		index = 0;

	t_astnode	*ast = parse_main(input, &index);
	return 0;
}

//++++++++++++++++++++++++++++++++++++TESTS

char	print_type(int type)
{
	switch (type)
	{
		case QUOTES:
			return ("is quotes");
		case EXSTAT:
			return ("is exit status");
		case APREDIR:
			return ("is append redirection");
		case HEREDOC:
			return ("is heredoc");
		case PIPE:
			return ("is pipe");
		case OPERATOR:
			return ("is operator");
	}
}

//test main
int	main(void)
{
	char	*input = "cat << EOF > file | wc -c |tr -d "" > file2";
	char	*last;
	t_tlst	**lst;

	int	i = 0;
	int	y = 0;
	int	len;
	while (input[i] != 0)
	{
		len = 0;
		while (type(input[i] == SEPARATOR))
			i++;
		while (type(input[i] != SEPARATOR)){
			i++;
			len++;
		}
	}
	last = malloc(sizeof(char) * (len + 1));
	last[len + 1] = 0;
	i -= len;
	while (input[i])
		input[i++] = last[y++];
	*lst = lexer(input);
	for (int i = 0; !cmp((*lst)[i].token->content, last); i++){
		printf ("%s (%s)", print_type((*lst)[i].token->type));
		free((*lst)[i].token->content);
		free((*lst)[i].token);
		*lst = (*lst)[i].next;
	}
	free(last);
}
