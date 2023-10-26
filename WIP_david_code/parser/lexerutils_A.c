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
inline int	type(const char *s, size_t i)
{
	if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		return (SEPR);
	if (s[i] == '\"' || s[i] == '\'')
		return (QUOT);
	if (s[i] == '$' && s[i + 1] == '?')
		return (EXST);
	else if (s[i] == '$')
		return (VARE);
	if (s[i] == '>' && s[i + 1] == '>')
		return (APRD);
	if (s[i] == '<' && s[i + 1] == '<')
		return (HERD);
	if (s[i] == '|')
		return (PIPE);
	if ((s[i] == '>' && s[i + 1] != '>') && (s[i] == '>' && s[i - 1] != '>'))
		return (REDR);
	if ((s[i] == '<' && s[i + 1] != '<') && (s[i] == '<' && s[i - 1] != '<'))
		return (REDL);
	return (WORD);
}

//finds first pipe in input
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

//finds first redirection in input
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

//cmp two strings returns bool if same string or not 
bool	cmp(char *content, const char *input)//WIP
{
	size_t	i;

	i = 0;
	while (content[i] == input[i] && (content[i] && input[i]))
		i++;
	if (!content[i] && !input[i])
		return (true);
	return (false);
}

/*
*	iterates size_t *i depending on the special character type
*/
bool	check_spec(const char *input, size_t *i)
{
	int	t;

	t = type(input, *i);
	if (t == EXST || t == HERD || t == APRD)
		*i += 2;
	else
		*i += 1;
	return (true);
}
