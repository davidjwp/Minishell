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

int	count_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
		i++;
	return (i);
}

int	get_type(char *token)
{
	int	i;

}

/*
*	start out by splitting the input and create a root for the tree 
*
*
*/
int	parser(char	*input)
{
	char	**split;
	t_ptn	*tokens;
	int		tokencnt;
	int		i;

	i = 0;
	split = ft_split(input, ' ');
	if (!split)
		return (free(input), 0);
	tokencnt = count_tokens(split);
	tokens = (t_ptn *)malloc(sizeof(t_ptn) * tokencnt);
	while (i < tokencnt)
	{
		tokens[i].string = split[i];
		tokens[i].position = tokencnt;
		tokens[i].type = get_type(tokens[i].string);
		tokens[i].child = NULL;
		tokens[i].parent = NULL;
		i++;
	}
	return (1);
}


// typedef struct parsetreenode{
// 	int						type;
// 	int						position;
// 	int						chnum;
// 	int						charnum;
// 	char					*string;
// 	struct parsetreenode	*parent;
// 	struct parsetreenode	**child;
// }			t_ptn;