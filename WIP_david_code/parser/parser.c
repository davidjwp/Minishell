/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:28:23 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/19 16:28:24 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Minishell.h"

int	get_type(char *token)
{
	int	i;

}



int	plant_tree(t_ptn *tokens)
{

}

int	create_tree(char **tokens_s, int tokens_n, t_ptn *tree)
{
	tree->
}

/*
*	start out by splitting the input and create a root for the tree 
*
*
*/
int	parser(char	*input)
{
	char	**tokens_s;
	t_ptn	*tokens;
	int		tokens_n;
	int		i;

	// i = 0;
	// if (!input)
	// 	return (0);
	// tokens_s = tokenize(input, &tokens_n, 0);
	// if (!tokens_s)
	// 	return (free(input), 0);
	// tokens = (t_ptn *)malloc(sizeof(t_ptn) * tokens_n);
	// while (i < tokens_n)
	// {
	// 	tokens[i].string = tokens_s[i];
	// 	tokens[i].position = tokens_n;
	// 	tokens[i].type = get_type(tokens[i].string);
	// 	tokens[i].child = NULL;
	// 	tokens[i].parent = NULL;
	// 	i++;
	// }
	// free_tokens(tokens_s);
	// plant_tree(tokens);
	return (1);
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
