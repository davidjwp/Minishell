/* ************************************************************************** */
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
*	(>),(<)			OPERATION
	(>>)			APREDIR
*	(<<)			HEREDOC
*	(|)				PIPE
*	($?)			EXSTAT
*	( ),(\t),(\n)	SEPARATOR
*/
int	type(char *s)
{
	if (*s == ' ' || *s == '\t' || *s == '\n')
		return (SEPARATOR);
	if (*s == '\"' || *s == '\'')
		return (QUOTES);
	if (*s == '$' && *s + 1 == '?')
		return (EXSTAT);
	else if (*s == '$')
		return (VARIABLE);
	if (*s == '>' && *s + 1 == '>')
		return (APREDIR);
	if (*s == '<' && *s + 1 == '<')
		return (HEREDOC);
	if (*s == '|')
		return (PIPE);
	if (*s == '>' || *s == '<')
		return (OPERATOR);
	return (WORD);
}

int	cmp(char *content, char *input)
{
	for (int i = 0; content[i] == input[i]; i++)
		if (!content[i])
			return (1);
	return (0);
}

int	check_spec(char *input, size_t *i)
{
	if (type(&input[*i]) == EXSTAT || type(&input[*i]) == HEREDOC ||\
	type(&input[*i]) == APREDIR)
		*i = 2;
	else
		*i = 1;
	return (1);
}

int	check_quote(char *input, size_t *i)
{
	*i++;
	while (type(&input[*i]) != QUOTES && &input[*i])
		*i++;
	if (!&input[*i])
		return (err_msg("unclosed quote"), 0);
	return (1);
}

int	built_in(char *input)
{
	char	**builtin;
	int		*type;
	int		i;

	i = 0;
	builtin = (char **){"echo", "cd", "pwd", "export", "unset", "env", \
	"exit", NULL};
	type = (int *){22, 33, 44, 55, 66, 77};
	while (builtin[i] != NULL)
	{
		if (cmp(builtin[i], input))
			return (type[i]);
		i++;
	}
	return (WORD);
}

//+++++++++++++++++++++++++++++LEXERUTILS_A_C

int	get_token_type(char	*token)
{
	int	builtin;

	if (type(token))
		return (type(token));
	else 
	{
		builtin = built_in(token);
		if (builtin)
			return (builtin);
	}
	return (COMMAND);
}

/*
*	this functions iterates over the token, i has a flag to check what to 
*	iterate over, the index is a pointer so that the higher scope index
*	can follow up
*/
int	it_token(char *input, size_t *i, int flag)
{
	if (flag == IT_SEP)
		while (type(&input[*i]) == SEPARATOR && &input[*i])
			*i++;
	if (!input[*i])
		return (0);
	else if (flag == IT_TOK)
	{
		if (type(&input[*i]) == QUOTES)
			return (check_quote(input, i));
		if (type(&input[*i]) != WORD)
			return (check_spec(input, i));
		while (type(&input[*i]) == WORD)
			*i++;
	}
	return (1);
}

/*
*
*/
char	*get_content(char *input, size_t *index, size_t *len)
{
	char	*content;
	int	i;

	i = 0;
	if (!it_token(input, len, IT_TOK))
		return (NULL);
	content = malloc(sizeof(char) * (*len + 1));
	if (!content)
		return (err_msg("get_content malloc fail"), NULL);
	content[*len + 1] = 0;
	while (i < *len)
	{
		content[i] = input[i];
		i++;
	}
	*index = len;
	return (content);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++createAST

t_astnode	*create_node(t_token token)
{
	t_astnode *newnode; 

	newnode = malloc(sizeof(t_astnode *));
	if (!newnode)
		return (NULL);
	newnode->token = token;
	return (newnode);
}

t_token	*get_token(char *input, int *index)
{
	t_token	*token;
	int	i;

	i = 0;
	if (!it_token(input[i], index, IT_SEP));
		return (NULL);
	token->content = get_content(input, index, &token->len);
	if (token->content == NULL)
		return (NULL);
	token->type = get_token_type(token->content);
	return (token);
}

t_astnode*	create_ast_node(t_token *token)
{
	t_astnode	*newnode;

	newnode = malloc(sizeof(t_astnode *));
	if (!newnode)
		return (NULL);
	newnode->token = token;
	return (token);
}

t_astnode*	parse_term(char *input, int *index)
{
	t_token	*token;

	token = get_token(input, index);
	if (token->type == WORD)
		return (create_ast_node(token));
	else if (token->type == QUOTES)
	{
		
	}
}

t_astnode	*parse_expression(char *input, int *index)
{
	t_astnode	*child;

	child = parse_term(input, index);
	if (child == NULL)
		return (NULL);//some freeing needed maybe

}


main(void)
{
	char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	int		index = 0;

	t_astnode	*ast = parse_expression(input, &index);
	return 0;
}


//not sure about the logic here 
// int	create_lexer(char *input, t_tlst *lstnode, int *tokcnt)
// {
// 	int	i;
// 	t_tlst	*newnode;
// 	t_token	*token;

// 	i = 0;
// 	*tokcnt += 1;
// 	token = (t_token *){0, 0, 0, NULL};
// 	if (!it_token(&input[i], &i, IT_SEP))
// 		return (0);
// 	token = malloc(sizeof(t_token));
// 	newnode = (t_tlst *){NULL, NULL};
// 	token->pos = *tokcnt;
// 	token->content = get_content(&input[i], &i, token->len);
// 	if (token->content == NULL)
// 		return (free(token), 0);
// 	token->type = get_token_type(token->content);
// 	if (input[i] != 0)
// 		create_lexer(&input[i], newnode, tokcnt);
// 	lstnode->token = token;
// 	lstnode->next = newnode;
// }

t_tlst	*lexer(char *input)
{
	int	tokcnt;
	t_tlst	*startnode;
	t_tlst	*endnode;

	tokcnt = 0;
	startnode = (t_tlst *){NULL, NULL};
	create_lexer(input, startnode, &tokcnt);

	//this should loop back the list to make it circular
	endnode = startnode;
	for (int i = 0; i < tokcnt; i++){
		endnode = endnode->next;
	}
	endnode->next = startnode;//idk about this stuff

	return (endnode);
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
