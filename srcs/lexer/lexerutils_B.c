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

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

/*
*   lexerutils_B contains the following functions :
*   check_quote(), built_in(), get_token_type(), it_token(), get_content()
*/
/*
*   will check for unclosed quotes and iterate index *i which corresponds to 
*   length in it_token's higher scope, this also gets the length of the token
*/
bool	check_quote(const char *input, size_t *i)
{
	if (type(input, *i) != 0 && !(type(input, *i) % 5) && input[*i + 1] == \
	input[*i])
		return (*i += 2, true);
	if ((type(input, *i) == DQUO))
	{
		*i += 1;
		while (type(input, *i) != DQUO && input[*i])
			*i += 1;
	}
	else if (type(input, *i) == SQUO)
	{
		*i += 1;
		while (type(input, *i) != SQUO && input[*i])
			*i += 1;
	}
	if (!input[*i])
		return (err_msg("unclosed quote"), false);
	*i += 1;
	return (true);
}

//compares the token with all builtin and returns it's builtin type if found
int	built_in(const char *input)
{
	char	*builtin[7];
	int		type[7];
	int		i;

	i = -1;
	while (++i < 8)
	{
		builtin[i] = (char *[8]){"echo", "cd", "pwd", "export", "unset", \
		"env", "exit", NULL}[i];
		type[i] = (int [7]){22, 33, 44, 55, 66, 77, 88}[i];
	}
	i = 0;
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
bool	it_token(const char *input, size_t *l_ind, int flag)
{
	if (flag == IT_SEP)
		while (type(input, *l_ind) == SEPR && input[*l_ind])
			*l_ind += 1;
	if (!input[*l_ind])
		return (false);
	else if (flag == IT_TOK)
	{
		if (type(input, *l_ind) != 0 && !(type(input, *l_ind) % 5))
			return (check_quote(input, l_ind));
		if (type(input, *l_ind) != WORD && input[*l_ind])
			return (check_spec(input, l_ind));
		while (type(input, *l_ind) == WORD && input[*l_ind])
			*l_ind += 1;
	}
	return (true);
}

//returns an allocated string from input for token and gets length of token
char	*get_content(const char *input, size_t *l_ind, size_t *len, int *err)
{
	char	*content;
	int		i;

	i = 0;
	if (!it_token(&input[*l_ind], len, IT_TOK))
		return (NULL);
	if (type(input, *l_ind) && !(type(input, *l_ind) % 5))
		return (get_quote(input, l_ind, len, err));
	content = malloc(sizeof(char) * (*len + 1));
	if (content == NULL)
		return (err_msg("get_content malloc fail"), *err = 1, NULL);
	content[*len] = 0;
	while (i < (int)*len)
	{
		content[i] = input[*l_ind];
		*l_ind += 1;
		i++;
	}
	return (content);
}
