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

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

t_astn	*parser(const char *input)
{
	t_astn		*tree;
	int	error;//might not need to pass it down
	size_t	g_ind;//might not even need to pass it down 

	error = 0;
	g_ind = 0;
	tree = create_ast(input, &g_ind, &error, NULL);
	if (error)
		return (0);
	/*parsing rules here*/
	//no > > so tree->right->left->token[0] == NULL or tree->right->left == NULL if tree->right->type == REDR
	//no < < 
	//you can have multiple files in those redirections but only the first one will be redirected
	//check file permissions for redirections, so 


	return (tree);
}