/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_A.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/23 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

bool	pipe_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL || node->left == NULL)
		return (*error += 1, syntax_error("|", cl), false);
	return (true);
}

bool	apr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->right == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	if (node->right->type == APRD)
		return (*error += 1, syntax_error(">>", cl), false);
	return (true);
}

bool	redr_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->left == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	return (true);
}

bool	redl_rules(t_astn *node, int *error, t_cleanup *cl)
{
	if (node->left != NULL)
		return (comd_rules(node->left->token, error, cl));
	if (node->right != NULL)
		return (comd_rules(node->right->token, error, cl));
	if (node->left == NULL || node->right == NULL)
		return (*error += 1, syntax_error("newline", cl), false);
	return (true);
}

bool	co_arr(t_token **token, int	*arr, int *len, int *error)
{
	int	i;

	i = 0;
	*len = 0;
	while (token[*len] != NULL)
		len += 1;
	arr = ft_calloc(*len, sizeof(int));
	if (arr == NULL)
		return (*error, err_msg("cr_arr malloc fail"), false);
	while (i < *len)
	{
		if (token[i]->co == 1)
			arr[i] = 1;
		else
			arr[i] = 0;
		i++;
	}
	return (true);
}

void	co_len(int *arr, t_token **token, int *i, int *error)
{
	int	len;

	len = 0;
	while (arr[*i])
	{
		len += ft_strlen(token[*i]->content);
		*i += 1;
	}
}

bool	co_tokens(t_token **token, int *error, t_cleanup *cl)
{
	
	int		*arr;
	int		len;
	int		i;

	if (!co_arr(token, arr, &len, error))
		return (false);
	while (token[i] != NULL)
	{
		ft_calloc(co_len(arr, token, &i, ));
		i++;
	}
}

bool	comd_rules(t_token **token, int *error, t_cleanup *cl, size_t y)
{
	char	*pathname;
	int		i;

	i = 0;
	if (!co_tokens(token, error, cl))
		return (false);
	pathname = cr_pathname(token[0]->content, cl->env, &cl->status, 0);
	if (pathname == NULL)
		return (*error += 1, false);
	else if (ft_strncmp(pathname, "ok", ft_strlen("ok")))
		free(pathname);
	while (token[i] != NULL)
	{
		while (token[i]->content[y])
		{
			if (type(token[i]->content, y) == HERD && token[i + 1] == NULL)
				return (*error += 1, syntax_error("newline", cl), false);
			y++;
		}
		y = 0;
		i++;
	}
	return (true);
}
