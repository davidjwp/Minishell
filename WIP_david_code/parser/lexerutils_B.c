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
bool	check_quote(const char *input, size_t *i)
{
	*i += 1;
	while (type(input, *i) != QUOT && input[*i])
	{
		if (type(input, *i) == VARE)
		
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
		if (type(input, *l_ind) == VARE && input[*l_ind])
			return (check_var(input, l_ind));
		if (type(input, *l_ind) == QUOT && input[*l_ind])
			return (check_quote(input, l_ind));
		if (type(input, *l_ind) != WORD && input[*l_ind])
			return (check_spec(input, l_ind));
		while (type(input, *l_ind) == WORD && input[*l_ind])
			*l_ind += 1;
	}
	return (true);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


//WIP
//you have to pass a cut input from l_ind 
char	get_var(const char *input, size_t *l_ind)
{
	char	*env;
	char	*var;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (input[len] >= 65 && input[len] <= 90 || input[len])
		len++;
	var = malloc(sizeof(char) * (len + 1));
	while (input[i] >= 65 && input[i] <= 90 || input[i])
	{
		var[i] = input[i];
		i++;
	}
	if (!getenv(var))
		return ()
	env = malloc(sizeof(char) * (ft_strlen(getenv(var)) + 1));
	while ()

}


char	*get_quote(const char *input, size_t *l_ind, size_t *len)
{
	char	*quote;
	int		i;

	i = 0;
	if (!check_quote(input, l_ind))
		return (0);
	*l_ind += 1;
	if (!it_token(input, l_ind, IT_TOK))
		return (0);
	
}

//returns an allocated string from input for token and gets length of token
char	*get_content(const char *input, size_t *l_ind, size_t *len)
{
	char	*content;
	int		i;

	i = 0;
	if (type(input, *l_ind) == QUOT)
		return (get_quote(input, l_ind, len));
	if (!it_token(&input[*l_ind], len, IT_TOK))
		return (NULL);
	content = malloc(sizeof(char) * (*len + 1));
	if (content == NULL)
		return (err_msg("get_content malloc fail"), NULL);
	content[*len] = 0;
	while (i < (int)*len)
	{
		content[i] = input[*l_ind];
		*l_ind += 1;
		i++;
	}
	return (content);
}

