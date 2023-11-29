/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_B.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/27 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"


int	add_line(t_herd *lines, char *line)
{
	t_herd	*new;
	t_herd	*tmp;
	int		len;
	int		i;

	i = -1;
	tmp = lines;
	len = ft_strlen(line);
	new = malloc(sizeof(t_herd));
	if (new == NULL)
		return (err_msg("add_line malloc fail"), 0);
	new->next = NULL;
	new->line = malloc(sizeof(char) * (len + 1));
	new->line[len] = 0;
	while (++i < len)
		new->line[i] = line[i];
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

void	free_herd(t_herd *lines)
{
	t_herd	*tmp;

	while (lines != NULL)
	{
		tmp = lines;
		lines = lines->next;
		free(tmp->line);
		free(tmp);
	}
}

int	comp_lines(t_herd *lines, char **line)
{
	char	*comp;
	t_herd	*tmp;
	size_t	len;

	len = 0;
	tmp = lines;
	while (tmp != NULL)
	{
		len += ft_strlen(tmp->line);
		tmp = tmp->next;
	}
	tmp = lines;
	comp = ft_calloc(len + 1, sizeof(char));
	if (comp == NULL)
		return (free(*line), 0);
	while (tmp != NULL)
	{
		ft_strcat(comp, tmp->line);
		tmp = tmp->next;
	}
	return (free(*line), *line = comp, 1);
}

t_herd	*lines_init(t_astn *node, int pos)
{
	t_herd	*lines;
	char	*line;
	int		len;
	int		i;

	i = -1;
	line = NULL;
	len = ft_strlen(node->token[pos + 1]->content);
	lines = malloc(sizeof(t_herd));
	if (lines == NULL)
		return (NULL);
	gnl(&line);
	if (ft_strncmp(line, node->token[pos + 1]->content, len) == 0)
		return (free(lines), rem_herd(node, pos), NULL);
	len = ft_strlen(line);
	lines->line = malloc(sizeof(char) * (len + 1));
	lines->line[len] = 0;
	if (lines->line == NULL)
		return (free(lines), NULL);
	lines->next = NULL;
	while (++i < len)
		lines->line[i] = line[i];
	return (lines);
}

// char	*here_doc(t_astn *node, int *error, int pos, t_cleanup *cl)
// {
// 	t_herd	*lines;
// 	char	*line;
// 	int		lmt_l;

// 	line = NULL;
// 	lines = lines_init(node, pos);
// 	if (lines == NULL)
// 		return (NULL);
// 	if (node->token[pos + 1] == NULL)
// 		return (syntax_error("newline", cl), *error += 1, NULL);
// 	lmt_l = ft_strlen(node->token[pos + 1]->content);
// 	while (gnl(&line))
// 	{
// 		if (ft_strncmp(line, node->token[pos + 1]->content, lmt_l) == 0)
// 			break ;
// 		if (!add_line(lines, line))
// 			return (free_herd(lines), NULL);
// 		free(line);
// 	}
// 	if (!comp_lines(lines, &line))
// 		return (free(line), free_herd(lines), NULL);
// 	return (free_herd(lines), line);
// }

// free(cmd->token[i]->content);
// free((t_token *)cmd->token[i]);