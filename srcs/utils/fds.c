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

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

//fd redirection of pipe or red type
int	fd_redirection(void *type, int redpipe, t_cleanup *cl)
{
	t_pipe	*_pip;
	t_red	*_red;
	int		error;

	if (redpipe & RES_IN)
		error = res_fd(STDI, cl);
	if (redpipe & RES_OUT)
		error = res_fd(STDO, cl);
	if (!error)
		return (0);
	if (redpipe & RED_RED)
	{
		_red = (t_red *)type;
		return (dup2(_red->out, STDOUT_FILENO), close(_red->out), 1);
	}
	else if (redpipe & RED_PIP)
	{
		_pip = (t_pipe *)type;
		dup2(_pip->pipe_fd[1], STDOUT_FILENO);
		close_pipe(_pip->pipe_fd);
	}
	return (1);
}

bool	res_fd(int type, t_cleanup *cl)
{
	t_fds	*head;

	head = cl->fds;
	while (cl->fds->next != head)
	{
		if (cl->fds->std == type)
			break ;
		cl->fds = cl->fds->next;
	}
	if (cl->fds->std == type)
		return (true);
	return (false);
}

//remove fd from the list i might not even need this at all
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
int	add_fd(t_fds *fd_lst, int fd)
{
	t_fds	*tmp;
	t_fds	*node;

	node = malloc(sizeof(t_fds *));
	if (!node)
		return (err_msg("add_fd malloc fail"), 0);
	node->fd = fd;
	tmp = fd_lst;
	while (tmp->next != fd_lst)
		tmp = tmp->next;
	tmp->next = node;
	node->next = fd_lst;
	return (1);
}

//initialize the fd list with stdin, stdout and stderror
t_fds	*init_fds(void)
{
	t_fds	*in;
	t_fds	*out;
	t_fds	*err;

	in = malloc(sizeof(t_fds));
	if (!in)
		return (err_msg("init_fds malloc fail"), NULL);
	out = malloc(sizeof(t_fds));
	if (!out)
		return (err_msg("init_fds malloc fail"), free(in), NULL);
	err = malloc(sizeof(t_fds));
	if (!in)
		return (err_msg("init_fds malloc fail"), free(in), free(out), NULL);
	in->fd = dup(STDIN_FILENO);
	out->fd = dup(STDOUT_FILENO);
	err->fd = dup(STDERR_FILENO);
	in->next = out;
	out->next = err;
	err->next = in;
	in->std = STDI;
	out->std = STDO;
	err->std = 2;
	return (in);
}
//this might lead to error in the grand loop, before i close all fds 
//stdin and out and error should always be restored but everytime i end a 
//shell loop i free everything and init again, this could be a problem idk