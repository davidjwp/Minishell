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
	if (node)
}

bool	parse(t_astn *node)
{
	if (node->left != NULL)
		parser_r(node->left);
	if (node->right != NULL)
		parser_r(node->right);
}

int	pipe()
{
	t_lus	pipe;

	pipe.o = open_file()
}



void	executor(t_astn *node)
{
	void	*gen;

	if (node->type == PIPE)
	{
		gen = (void *)pipe();
		executor(node->right);
		

	}


}

//separate
int	pre_exe(const char *input, )
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
