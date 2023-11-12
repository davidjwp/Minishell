/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:58:33 by rmohamma          #+#    #+#             */
/*   Updated: 2023/10/16 10:46:59 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

/*Nous allons écrire une fonction qui va stocker notre commande 
(sans les espaces) dans un char **C qui donnera :*/
char	**split(char *input, char *limit)
{
	char	*ptr = NULL;
	char	**token = NULL;
	size_t	idx = 0;

	// split sur les espaces
	ptr = strtok(input, limit);
	while (ptr)
	{
		token = (char **)realloc(token, ((idx + 1) * sizeof(char *)));
		token[idx] = strdup(ptr);
		ptr = strtok(NULL, limit);
		++idx;
	}
	// On alloue un element qu'on met a NULL a la fin du tableau
	token = (char **)realloc(token, ((idx + 1) * sizeof(char *)));
	token[idx] = NULL;
	return (token);
}
