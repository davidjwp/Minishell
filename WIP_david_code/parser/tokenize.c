/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:48:03 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/22 21:48:06 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//WILL DELETE
#include "../Minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
		free(tokens[i++]);
	free(tokens);
}

/*
*	This function will go through the quote and count it as one token, if two
*	different quotes are right next to each other it will count as one token.
*
*	The function also checks for unclosed quotes, everything in the quote is 
*	irrelevant as all of it is counted all the same as text.
*/
int	quote(char *input, char q_type, int *iptr)
{
	int	quote;

	quote = 1;
	while (input[*iptr] != '\n')
	{
		if (!quote && (input[*iptr] == 32 || input[*iptr] == 9 || \
		input[*iptr] == 10))
			return (1);
		if (input[*iptr] == q_type)
			quote = 0;
		*iptr++;
		if (!quote && (input[*iptr] == '\'' || input[*iptr] == '\"'))
			quote = 1;
	}
	if (quote && input[*iptr] == '\n')
		return (err_msg("Unclosed quote"), 0);
	return (2);
}

static char	*cpy_token(char *input, char c, int l)
{
	char	*token;
	int		i;

	i = -1;
	if (c != 0)
		quote(input, c, &l);
	else
		while (input[l] && (input[l] != 32 && input[l] != 9 && input[l] != 10))
			l++;
	token = (char *)malloc(l + 1);
	if (token == NULL)
		return (err_msg("cpy_token malloc fail"), NULL);
	while (i++ < l)
		token[i] = input[i];
	token[i] = '\0';
	return (token);
}

//32 for space 9 for tab and 10 for newline
int	get_tokens_n(char *input)
{
	int	tokens_n;
	int	i;

	i = 0;
	tokens_n = 0;
	while (input[i] != '\n')
	{
		while (input[i] && (input[i] == 32 || input[i] == 9 || input[i] == 10))
			i++;
		if (!input[i])
			return (tokens_n);
		tokens_n++;
		if (input[i] == '\'' || input[i] == '\"')
			if (!quote(&input[i], input[i], &i++))
				return (0);
		else
			while (input[i] && (input[i] == 32 && input[i] == 9 && input[i] \
			== 10))
				i++;
	}
	return (tokens_n);
}

/*
*	list of the special characters that are explicitily asked in the subject
*	anything not asked is not required.
*
*	(') single quotes which do no interpretation
*	(") double quotes which only interpret $ for variables
*	($) dollar sign for variables including env
*	(>) output redirection
*	(<) input redirection
*	(<<) heredoc with delimiter and read until a line containing the delimiter
*		is seen, does not have to update history
*	(>>) output redirection but appends the text instead of writing over
*	(|) pipes
*	($?) this expands to the exit status of the last executed foreground
*	pipeline meaning what's left in the pipe if it has anything in it
*/

char	**tokenize(char *input, int *tokens_n, int tokens_i)
{
	char	**tokens;
	int		i;

	i = 0;
	*tokens_n = get_tokens_n(input, tokens_n);
	if (!*tokens_n)
		return (NULL);
	tokens = malloc(sizeof(char *) * tokens_n + 1);
	if (!tokens)
		return (err_msg("Tokenize malloc fail"), NULL);
	while (input[i])
	{
		while (input[i] && (input[i] == 32 || input[i] == 9 || input[i] == 10))
			i++;
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
			tokens[tokens_i] = cpy_tokens(&input[i], input[i], 1);
		else
			tokens[tokens_i] = cpy_tokens(&input[i], (char)0, 0);
		if (!tokens[tokens_i])
			return (free_tokens(tokens), NULL);
		token_i++;
		while (input[i] && (input[i] != 32 && input[i] != 9 && input[i] != 10))
			i++;
	}
	return (tokens[i] = NULL, tokens);
}

// void	free_tokens(char **tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (tokens[i] != NULL)
// 		free(tokens[i++]);
// 	free(tokens);
// }

// int	special_char(char c)
// {
// 	if (c == '$' || c == '#' || c == '!' || c == '*' || c == '?' || c == '{'\
// 	|| c == '}' || c == )
// }
// //special $ # ! * ? {} [] () $()
// //operator > & && | || <

// /*
// *	This function will go through the quote and count it as one token, if two
// *	different quotes are right next to each other it will count as one token.
// *
// *	The function also checks for unclosed quotes, everything in the quote is 
// *	irrelevant as all of it is counted all the same as text.
// */
// int	quote(char *input, char q_type, int *iptr)
// {
// 	int	quote;

// 	quote = 1;
// 	while (input[*iptr] != '\n')
// 	{
// 		if (!quote && (input[*iptr] == 32 || input[*iptr] == 9 || \
// 		input[*iptr] == 10))
// 			return (1);
// 		if (input[*iptr] == q_type)
// 			quote = 0;
// 		*iptr++;
// 		if (!quote && (input[*iptr] == '\'' || input[*iptr] == '\"'))
// 			quote = 1;
// 	}
// 	if (quote && input[*iptr] == '\n')
// 		return (err_msg("Unclosed quote"), 0);
// 	return (2);
// }

// static char	*cpy_token(char *input, char c, int l)
// {
// 	char	*token;
// 	int		i;

// 	i = -1;
// 	if (c != 0)
// 		quote(input, c, &l);
// 	else
// 		while (input[l] && (input[l] != 32 && input[l] != 9 && input[l] != 10))
// 			l++;
// 	token = (char *)malloc(l + 1);
// 	if (token == NULL)
// 		return (err_msg("cpy_token malloc fail"), NULL);
// 	while (i++ < l)
// 		token[i] = input[i];
// 	token[i] = '\0';
// 	return (token);
// }

// //32 for space 9 for tab and 10 for newline
// int	get_tokens_n(char *input)
// {
// 	int	tokens_n;
// 	int	i;

// 	i = 0;
// 	tokens_n = 0;
// 	while (input[i])
// 	{
// 		while (input[i] && (input[i] == 32 || input[i] == 9 || input[i] == 10))
// 			i++;
// 		if (!input[i])
// 			return (tokens_n);
// 		tokens_n++;
// 		if (input[i] == '\'' || input[i] == '\"')
// 			if (!quote(&input[i], input[i], &i++))
// 				return (0);
// 		else if (special_char(input[i]))

// 		else
// 			while (input[i] && (input[i] == 32 && input[i] == 9 && input[i] \
// 			== 10))
// 				i++;
// 	}
// 	return (tokens_n);
// }
// // $ " ' # ! * ? [] {} ( | & > $() * bonus && || 

// /*
// *	The tokenize function will check the input for proper quotes
// *
// *	this is pretty much a split modified for quotes where i keep tokens_n
// *	(for tokens number) for later
// */
// char	**tokenize(char *input, int *tokens_n, int tokens_i)
// {
// 	char	**tokens;
// 	int		i;

// 	i = 0;
// 	*tokens_n = get_tokens_n(input, tokens_n);
// 	if (!*tokens_n)
// 		return (NULL);
// 	tokens = malloc(sizeof(char *) * tokens_n + 1);
// 	if (!tokens)
// 		return (err_msg("Tokenize malloc fail"), NULL);
// 	while (input[i])
// 	{
// 		while (input[i] && (input[i] == 32 || input[i] == 9 || input[i] == 10))
// 			i++;
// 		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
// 			tokens[tokens_i] = cpy_tokens(&input[i], input[i], 1);
// 		else
// 			tokens[tokens_i] = cpy_tokens(&input[i], (char)0, 0);
// 		if (!tokens[tokens_i])
// 			return (free_tokens(tokens), NULL);
// 		token_i++;
// 		while (input[i] && (input[i] != 32 && input[i] != 9 && input[i] != 10))
// 			i++;
// 	}
// 	return (tokens[i] = NULL, tokens);
// }
