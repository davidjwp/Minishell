/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_C.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/28 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

int	gnl(char **line)
{
	char	*buf;
	int		n;
	char	c;
	int		i;

	i = 0;
	write (1, "heredoc> ", 9);
	buf = malloc(sizeof(char) * BUFSIZ);
	n = read(STDIN_FILENO, &c, 1);
	while (n && c != '\n' && c != '\0')
	{
		if (c != 'n' && c != '\0')
			buf[i] = c;
		n = read(STDIN_FILENO, &c, 1);
		i++;
	}
	buf[i] = '\n';
	buf[++i] = 0;
	*line = buf;
	return (n);
}

int	rem_herd(t_astn *node,  int pos)
{
	int	i;

	free(node->token[pos]->content);
	free((t_token *)node->token[pos]);
	free(node->token[pos + 1]->content);
	free((t_token *)node->token[pos + 1]);
	if (node->token[pos + 2] != NULL)
		return (node->token[pos] = NULL, 0);
	i = 0;
	while (node->token[pos + i + 2] != NULL)
	{
		node->token[pos + i] = node->token[pos + i + 2];
		i++;
	}
	node->token[pos + i] = NULL;
	return (1);
}

//this is not a safe strcat but i only use it in a specific occasion
size_t	ft_strcat(char *dest, const char *src)
{
	unsigned int	index;
	size_t			d_len;

	index = 0;
	d_len = ft_strlen(dest);
	while (src[index])
	{
		dest[d_len + index] = src[index];
		index++;
	}
	dest[d_len + index] = 0;
	return (1);
}
