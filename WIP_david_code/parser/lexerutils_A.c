/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_A.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:31:16 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/30 17:31:17 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
*	lexerutils_A contains the following functions :
*	type(), input_pipe(), input_red(), cmp(), check_spec()
*/
//returns type for first pointed chars in *s
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

/*
*	if pipe found return input index at pipe as integer so pipe value
*	if pipe not found return index end of input which is 0  
*/
int	input_pipe(char *input)
{
	int	i;

	i = 0;
	while (type(&input[i]) != PIPE && input[i])
		i++;
	return ((int)input[i]);
}

//same as input pipe
int	input_red(char *input)
{
	int	i;

	i = 0;
	while (type(&input[i]) != OPERATOR && input[i])
		i++;
	return ((int)input[i]);
}

//cmp two strings returns bool if same string or not 
bool	cmp(char *content, char *input)
{
	int	i;

	i = 0;
	while (content[i] == input[i])
	{
		if ((!content[i] || type(&content[i]) == SEPARATOR) && !input[i])
			return (true);
		i++;
	}
	return (false);
}

/*
*	iterates size_t *i depending on the special character type
*	here *i is the length of the token in higher scope it_token 
*/
bool	check_spec(char *input, size_t *i)
{
	if (type(&input[*i]) == EXSTAT || type(&input[*i]) == HEREDOC || \
	type(&input[*i]) == APREDIR)
		*i = 2;
	else
		*i = 1;
	return (true);
}
