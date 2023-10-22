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
bool	check_quote(const char *input, size_t *len, size_t *i)
{
	*i += 1;
	*len += 1;
	while (type(input, *i) != QUOT && input[*i])
	{
		*i += 1;
		*len += 1;
	}
	if (!input[*i])
		return (err_msg("unclosed quote"), false);
	return (true);
}

//compares the token with all builtin and returns it's builtin type if found
int	built_in(const char *input)
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
int	get_token_type(char *token)
{
	int	builtin;

	if (type(token, 0))
		return (type(token, 0));
	else
	{
		builtin = built_in(token);
		if (builtin)
			return (builtin);
	}
	return (WORD);
}

/*
*   iterates the token while giving length of token, also 
*	iterates over SEPARATORS and checks unclosed quotes 
*/
bool	it_token(const char *input, size_t *res, size_t *i, int flag)
{
	if (flag == IT_SEP)
	{
		while (type(input, *res) == SEPR && input[*res])
		{
			*i += 1;
			*res += 1;
		}
	}
	if (!input[*res])
		return (false);
	else if (flag == IT_TOK)
	{
		if (type(input, *res) == QUOT && input[*res])
			return (check_quote(input, res, i));
		if (type(input, *res) != WORD && input[*res])
			return (check_spec(input, res, i));
		while (type(input, *res) == WORD && input[*res])
		{
			*res += 1;
			*i += 1;
		}
	}
	return (true);
}

//returns an allocated string from input for token and gets length of token
char	*get_content(const char *input, size_t *index, size_t *res)
{
	char	*content;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!it_token(input, len, index, IT_TOK))
		return (NULL);
	content = malloc(sizeof(char) * (*res + 1));
	if (content == NULL)
		return (err_msg("get_content malloc fail"), NULL);
	content[*res + 1] = 0;
	*index -= *res;
	while (i < (int)*res)
	{
		content[i] = input[*index];
		*index += 1;
		i++;
	}
	return (content);
}
