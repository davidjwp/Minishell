/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerutils_C.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:47:16 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/30 20:47:17 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
*	lexerutils_C contains the following functions :
*	get_token(), nbr_token(), free_tokens(), free_cmd_node()
*/
//returns the token struct with allocated content and type + length
t_token	*get_token(const char *input, size_t *l_ind, t_token *token)
{
	token->len = 0;
	if (!it_token(input, l_ind, IT_SEP))
		return (NULL);
	token->content = get_content(input, l_ind, &token->len);
	if (token->content == NULL)
		return (NULL);
	token->type = get_token_type(token->content);
	it_token(input, l_ind, IT_SEP);
	return (token);
}

//counts the number of tokens until a pipe or redirection is found
int	nbr_token(const char *input)
{
	size_t	l_ind;
	int		tokcnt;
	int		t;

	l_ind = 0;
	tokcnt = 0;
	if (!*input)
		return (0);
	t = type(input, l_ind);
	while (t != REDL && t != REDR && t != APRD && t != PIPE && input[l_ind])
	{
		it_token(input, &l_ind, IT_SEP);
		t = type(input, l_ind);
		if (t != REDL && t != REDR && t != APRD && t != PIPE && input[l_ind])
			tokcnt += 1;
		else
			break ;
		it_token(input, &l_ind, IT_TOK);
	}
	return (tokcnt);
}

/*
*	free the tokens up to last, only used while assigning allocated token
*	structures to the token struct array so that it only frees what has been
*	allocated 
*/ 
void	free_tok(t_token **tokens, int last)
{
	int	i;

	i = 0;
	while (i < last)
	{
		free(tokens[i]->content);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

//frees the whole command node
void	free_cmd_node(t_astn *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
		return ;
	while (cmd->token[i] != NULL)
	{
		free(cmd->token[i]->content);
		free((t_token *)cmd->token[i]);
		i++;
	}
	free(cmd->token);
	free(cmd);
}

//free the redirection node
void	free_node(t_astn *red)
{
	free_cmd_node(red->left);
	free_cmd_node(red->right);
	free(red);
}
