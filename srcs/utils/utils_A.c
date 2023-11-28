/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_A.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/24 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

char	*print_type(int type)
{
	char	*types[14];
	int		num[14];
	int		i;

	i = -1;
	if (type != 0 && !(type % 11))
		return ((char *[7]){"ECHO", "CD", "PWD", "EXPORT", "UNSET", "ENV"\
		, "EXIT"}[(type / 10) - 2]);
	while (++i < 14)
	{
		types[i] = (char *[15]){"WORD", "SEPR", "HERD", "EXST", "APRD", \
		"SQUO", "ARGT", "OPER", "REDL", "VARE", "DQUO", "BUIT", "REDR", \
		"COMD", "PIPE"}[i];
		num[i] = (int [14]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}[i];
	}
	i = 0;
	while (type != num[i])
		i++;
	return (types[i]);
}

void	print_tree(t_astn *node)
{
	int	i;

	i = 0;
	if (node->left != NULL)
		print_tree(node->left);
	if (node->right != NULL)
		print_tree(node->right);
	if (node->type != COMD)
		printf ("______\nnode %s %p\nleft %p\nright %p\ntoken %p\nparent %p\n"\
		, print_type(node->type), node, node->left, node->right, \
		node->token, node->parent);
	else
	{
		printf ("______\nnode %s %p\nleft %p\nright %p\ntoken %p\nparent %p\n"\
		, print_type(node->type), node, node->left, node->right, node->token, \
		node->parent);
		while (node->token[i] != NULL)
		{
			printf("%s %li %s\n", node->token[i]->content, node->token[i]->len \
			, print_type(node->token[i]->type));
			i++;
		}
	}
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	ptr_size;

	ptr_size = (int)(nmemb * size);
	if (size != 0 && nmemb != (size_t)ptr_size / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (ptr_size--)
		ptr[ptr_size] = 0;
	return (ptr);
}

void	print_sh_env(t_env *sh_env)
{
	FILE	*_file;
	t_env	*tmp;

	tmp = sh_env;
	_file = fopen("sh_env_file", "w+");
	fprintf(_file, "%s=%s\n", sh_env->name, sh_env->value);
	sh_env = sh_env->next;
	while (sh_env != tmp)
	{
		fprintf(_file, "%s=%s\n", sh_env->name, sh_env->value);
		sh_env = sh_env->next;
	}
	fclose(_file);
}
