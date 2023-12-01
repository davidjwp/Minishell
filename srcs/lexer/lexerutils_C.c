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

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

/*
*	lexerutils_C contains the following functions :
*	get_token(), nbr_token(), free_tok(), free_cmd_node(), free_node()
*/
//counts the number of tokens until a pipe or redirection is found
int	nbr_token(const char *input, size_t l_ind, int tokcnt)
{
	int		t;

	if (!*input)
		return (0);
	t = type(input, l_ind);
	while (t != REDL && t != REDR && t != APRD && t != PIPE && input[l_ind])
	{
		it_token(input, &l_ind, IT_SEP);
		t = type(input, l_ind);
		if (!input[l_ind])
			break ;
		if ((t == SQUO || t == DQUO))
		{
			if (input[l_ind + 1] != input[l_ind])
				tokcnt++;
		}
		else if (t != REDL && t != REDR && t != APRD && t != PIPE)
			tokcnt += 1;
		else if (t == REDL || t == REDR || t == APRD || t == PIPE)
			break ;
		if (!it_token(input, &l_ind, IT_TOK))
			return (0);
	}
	return (tokcnt);
}

//enum e_type{
//	WORD,0
//	SEPR,1
//	HERD,2
//	EXST,3
//	APRD,4
//	SQUO,5
//	ARGT,6
//	OPER,7
//	REDL,8
//	VARE,9
//	DQUO,10
//	BUIT,11
//	REDR,12
//	COMD,13
//	PIPE,14
//};	

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
void	free_cmd_node(t_astn *cmd, bool cmdbool)
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
	if (cmdbool)
		free(cmd);
}

char	*get_quote(const char *input, size_t *l_ind, size_t *len, int *err)
{
	char	*content;
	int		i;

	i = 0;
	*len -= 2;
	if (input[*l_ind + 1] == input[*l_ind])
		return (*l_ind += 2, NULL);
	content = malloc(sizeof(char) * (*len + 1));
	if (content == NULL)
		return (err_msg("get_quote malloc fail"), *err = 1, NULL);
	content[*len] = 0;
	while (i < (int)*len)
	{
		*l_ind += 1;
		content[i] = input[*l_ind];
		i++;
	}
	return (content);
}

int	cut_len(const char *input, int flag)
{
	int	len;
	int	t;

	len = 0;
	t = type(input, len);
	if (flag == C_PIPE)
	{
		while (input[len] && type(input, len) != PIPE)
			len++;
	}
	else if (flag == C_RED)
	{
		while (input[len] && (!t || t % 4 != 0))
		{
			if (t == HERD)
				len += 2;
			else
				len += 1;
			t = type(input, len);
		}
	}
	return (len);
}
