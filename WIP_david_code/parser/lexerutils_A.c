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
int	type(const char *s, size_t i)
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

//finds pipe if there is one and returns it's position if not zero
int	input_pipe(const char *input)
{
	size_t	i;

	i = 0;
	while (type(input, i) != PIPE && input[i])
		i++;
	if (input[i])
		return (i);
	return (0);
}

//same as input pipe
int	input_red(const char *input)
{
	size_t	i;
	int	t;

	i = 0;
	t = type(input, i);
	while (t != REDL && t != REDR && t != APRD && input[i])
	{
		t = type(input, i);
		if (t == REDL && t == REDR && t == APRD && input[i])
			break ;
		i++;
	}
	if (input[i])
		return (i);
	return (0);
}

//cmp two strings returns bool if same string or not 
bool	cmp(char *content, const char *input)
{
	size_t	i;

	i = 0;
	while (content[i] == input[i])
	{
		if ((!content[i] || type(content, i) == SEPR) && !input[i])
			return (true);
		i++;
	}
	return (false);
}

/*
*	iterates size_t *i depending on the special character type
*	here *i is the length of the token in higher scope it_token 
*/
bool	check_spec(const char *input, size_t *len, size_t *i)
{
	int	t;

	t = type(input, *i);
	if (t == EXST || t == HERD || t == APRD)
		*len += 2;
	else
		*len += 1;
	*i += *len;
	return (true);
}
