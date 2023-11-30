/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:03:33 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/30 16:03:34 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SH_functs.h"
#include "../includes/SH_structs.h"


int	get_herd_pos(t_astn *node)
{
	int	i;

	i = 0;
	while (node->token[i]->type != HERD)
		i++;
	return (i);
}

void	cpy_tok(t_token *cpy, t_token *tok)
{
	char	*cpycont;
	int		len;

	if (tok != NULL)
	{
		cpy->len = tok->len;
		cpy->type = tok->type;
		len = ft_strlen(tok->content);
		cpycont = malloc(sizeof(char) * (len + 1));
		if (cpycont != NULL)
		{
			cpycont[len] = 0;
			while (len--)
				cpycont[len] = tok->content[len];
			cpy->content = cpycont;
		}
		else
		{
			err_msg("cpy_tok malloc fail");
			free(cpy);
			cpy = NULL;
		}
	}
}

int	cpy_token(t_astn *node)
{
	t_token	**cpy;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (node->token[len] != NULL)
		len++;
	len -= 2;
	cpy = (t_token **)malloc(sizeof(t_token) * len);
	cpy[len] = NULL;
	while (len--)
	{
		if (node->token[i]->type == HERD)
			i += 2;
		cpy[i] = (t_token *)malloc(sizeof(t_token));
		if (cpy[i] == NULL)
			return (free_tok(cpy, i), err_msg("cpy_token malloc fail"), 0);
		cpy_tok(cpy[i], node->token[i]);
		if (cpy[i] == NULL)
			return (free_tok(cpy, i), 0);
		i++;
	}
	return (free_cmd_node(node, false), node->token = cpy, 1);
}

int	exe_herd(t_astn *node, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;
	int	error;

	error = 0; 
	if (pipe(p.pipe_fd) == -1)
		return (err_msg("exe_herd pipe fail"), 0);
	if (!fd_redirection(&p, RES_OUT | RED_PIP, cl))
		return (0);
	here_doc(node, &error, get_herd_pos(node), cl);
	if (error)
		return (0);
	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("exe_herd fork fail"), 0);
	if (!p.l_pid)
	{
		if (!cpy_token(node))
			return (clean_up(cl, CL_ALL), exit(EXIT_FAILURE), 0);
		if (!fd_redirection(&p, RES_IN | RED_PIP, cl))
			return (clean_up(cl, CL_ALL), exit(EXIT_FAILURE), 0);
		execute(node, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	return (wait(&cl->status), 1);
}

char	*here_doc(t_astn *node, int *error, int pos, t_cleanup *cl)
{
	t_herd	*lines;
	char	*line;
	int		lmt_l;

	line = NULL;
	lines = lines_init(node, pos);
	if (lines == NULL)
		return (NULL);
	if (node->token[pos + 1] == NULL)
		return (syntax_error("newline", cl), *error += 1, NULL);
	lmt_l = ft_strlen(node->token[pos + 1]->content);
	while (gnl(&line))
	{
		if (ft_strncmp(line, node->token[pos + 1]->content, lmt_l) == 0)
			break ;
		if (!add_line(lines, line))
			return (free_herd(lines), NULL);
		free(line);
	}
	if (!comp_lines(lines, &line))
		return (free(line), free_herd(lines), NULL);
	return (free_herd(lines), line);
}
