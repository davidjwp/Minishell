/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:31:16 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/21 17:31:17 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SH_functs.h"
#include "../includes/SH_structs.h"

//fd redirection of pipe or red type
void	fd_redirection(void *type, bool redpipe)
{
	t_pipe	*_pip;
	t_red	*_red;

	if (redpipe)
	{
		_red = (t_red *)type;
		dup2(_red->out, STDOUT_FILENO);
		close(_red->out);
	}
	else if (!redpipe)
	{
		_pip = (t_pipe *)type;
		if (!_pip->l_pid)
			dup2(_pip->pipe_fd[1], STDOUT_FILENO);
		else if (!_pip->r_pid)
			dup2(_pip->pipe_fd[0], STDIN_FILENO);
		close_pipe(_pip->pipe_fd);
	}
}

void	mv_to_fd(t_cleanup *cl, )
{
	while 
}

//remove fd from the list
void	rem_fd(t_fds *fd_lst, int fd)
{
	t_fds	*tmp;
	t_fds	*back;

	tmp = fd_lst;
	back = tmp;
	if (tmp->fd == fd)
		while (back->next != tmp)
			back = back->next;
	while (tmp->fd != fd && tmp->next != fd_lst)
	{
		back = tmp;
		tmp = tmp->next;
	}
	if (tmp->fd == fd)
	{
		back->next = tmp->next;
		free(tmp);
	}
}

//add fd to the list
void	add_fd(t_fds *fd_lst, int fd)
{
	t_fds	*tmp;
	t_fds	*node;

	node = malloc(sizeof(t_fds *));
	node->fd = fd;
	tmp = fd_lst;
	while (tmp->next != fd_lst)
		tmp = tmp->next;
	tmp->next = node;
	node->next = fd_lst;
}

//initialize the fd list with stdin, stdout and stderror
t_fds	*init_fds(void)
{
	t_fds	*in;
	t_fds	*out;
	t_fds	*err;

	in = malloc(sizeof(t_fds *));
	out = malloc(sizeof(t_fds *));
	err = malloc(sizeof(t_fds *));
	in->fd = dup(STDIN_FILENO);
	out->fd = dup(STDOUT_FILENO);
	err->fd = dup(STDERR_FILENO);
	in->next = out;
	out->next = err;
	err->next = in;
	return (in);
}
//this might lead to error in the grand loop, before i close all fds 
//stdin and out and error should always be restored but everytime i end a 
//shell loop i free everything and init again, this could be a problem idk