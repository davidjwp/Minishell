/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_B.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:54:51 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/30 17:54:52 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
*   lexerutils_B contains the following functions :
*   check_quote(), built_in(), get_token_type(), it_token(), get_content()
*/
/*
*   will check for unclosed quotes and iterate index *i which corresponds to 
*   length in it_token's higher scope, this also gets the length of the token
*/
bool	check_quote(char *input, size_t *i)
{
	*i++;
	while (type(&input[*i]) != QUOTES && input[*i])
		*i++;
	if (!input[*i])
		return (err_msg("unclosed quote"), false);
	return (true);
}

//compares the token with all builtin and returns it's builtin type if found
int	built_in(char *input)
{
	char	*builtin[7];
	int		type[7];
	int		i;

	i = -1;
	while (++i < 7)
	{
		builtin[i] = (char* [8]){"echo", "cd", "pwd", "export", "unset", \
		"env", "exit", NULL}[i];
		type[i] = (int [7]){22, 33, 44, 55, 66, 77, 88}[i];
	}
	while (builtin[i] != NULL)
	{
		if (cmp(builtin[i], input))
			return (type[i]);
		i++;
	}
	return (WORD);
}

//finds the type for the token, if not special character or builtin then word
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
	return (WORD);
}

/*
*   iterates the input with higher scope index which corresponds to length of 
*   token, also iterates over SEPARATORS and checks unclosed quotes
*/
bool	it_token(char *input, size_t *i, int flag)//as is
{
	if (flag == IT_SEP)
		while (type(&input[*i]) == SEPARATOR && input[*i])
			*i++;
	if (!input[*i])
		return (false);
	else if (flag == IT_TOK)
	{
		if (type(&input[*i]) == QUOTES)
			return (check_quote(input, i));
		if (type(&input[*i]) != WORD)
			return (check_spec(input, i));
		while (type(&input[*i]) == WORD)
			*i++;
	}
	return (true);
}

//returns an allocated string from input for token and gets length of token
char	*get_content(char *input, size_t *index, size_t *len)//as is 
{
	char	*content;
	int		i;

	i = 0;
	if (!it_token(input, len, IT_TOK))
		return (NULL);
	content = malloc(sizeof(char) * (*len + 1));
	if (content == NULL)
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
