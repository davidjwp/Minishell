/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/10/30 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

bool	parser_r(t_astn *node)
{
	if 
}

bool	parse(t_astn *node)
{
	if (node->left != NULL)
		parser_r(node->left);
	if (node->right != NULL)
		parser_r(node->right);
	
}

int	b_exe(t_astn *node)
{

}

int	a_exe(t_astn *node)
{
	if (node->type == PIPE)
	{
		b_exe(node->left);
	}
	
}



//separate
int	execute(const char *input, )
{
	t_astn	*ast_root;
	int		error;
	int		index;

	error = 0;
	index = 0;
	ast_root = create_ast(input, &index, &error, NULL);
	if (error || ast_root == NULL)
		return (0);
	if (!parser(ast_root))
		return (0);
	if (ast_root->type == PIPE)
		pipex();
}