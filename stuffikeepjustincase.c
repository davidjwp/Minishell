int	sing_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;

	if (pipe(p.pipe_fd) == -1)
		return (err_msg("sh_pipe pipe error"), 0);
	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("sh_pipe fork error"), 0);
	if (!p.l_pid)
	{
		if (!fd_redirection(&p, RES_OUT | RED_PIP, cl))
			exit(EXIT_FAILURE);
		shell_loop(tree->left, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	p.r_pid = fork();
	if (p.r_pid == -1)
		return (err_msg("sh_pipe pipe fork error"), 0);
	if (!p.r_pid)
	{
		if (!fd_redirection(&p, RES_IN | RED_PIP, cl))
			exit(EXIT_FAILURE);
		shell_loop(tree->right, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	return (wait_pipe(p), 0);
}

/*
*	restore the file descriptor, this function doesn't really restore the fd
*	instead it will put the cleanup fd with the matching fd at the top of the 
*	list using fstat to compare inode and placement and then i can restore 
*	from sh_pipe or sh_red whatever the correct fd is by simply using the
*	 top of the fd list
*/
int	res_fd(int fd, t_cleanup *cl)
{
	t_fds		*tmp;
	struct stat	stat1;
	struct stat	stat2;

	tmp = cl->fds;
	if (fstat(fd, &stat1) < 0)
		return (0);
	if (fstat(cl->fds->fd, &stat2) < 0)
		return (0);
	while (cl->fds->next != tmp)
	{
		if ((stat2.st_dev == stat1.st_dev && stat2.st_ino == stat1.st_ino))
			return (1);
		cl->fds = cl->fds->next;
		if (fstat(cl->fds->fd, &stat2) < 0)
			return (0);
	}
	if ((stat2.st_dev == stat1.st_dev && stat2.st_ino == stat1.st_ino))
		return (1);
	while (cl->fds != tmp)
		cl->fds = cl->fds->next;
	return (0);
}

void	rem_pid(int pid, t_pids *pids)
{
	t_pids	*tmp;
	t_pids	*link;

	tmp = pids;
	while (tmp->pid != pid && tmp->next != NULL)
	{
		link = tmp;
		tmp = tmp->next;
	}
	if (tmp->pid == pid && tmp->next != NULL)
	{
		link->next = tmp->next;
		free(tmp);
		tmp = NULL;
	}
	else if (tmp->pid == pid && tmp->next == NULL)
	{
		free(tmp);
		tmp = NULL;
	}
}

int	get_pid(t_pids *pids)
{
	t_pids	*tmp;

	tmp = pids;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp->pid);
}

int	add_pid(int pid, t_pids *pids)
{
	t_pids	*tmp;
	t_pids	*new;

	if (pid == -1)
		return (err_msg("fork error"), 0);
	new = malloc(sizeof(t_pids));
	if (new == NULL)
		return (err_msg("add_pid malloc fail"), 0);
	new->next = NULL;
	new->pid = pid;
	tmp = pids;
	if (tmp == NULL)
		return (pids = new, 1);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

// creates a pipe by forking in the left then right side of the pipe
int	sing_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;

	if (pipe(p.pipe_fd) == -1)
		return (err_msg("sh_pipe pipe error"), 0);
	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("sh_pipe fork error"), 0);
	if (!p.l_pid)
	{
		if (!fd_redirection(&p, RES_OUT | RED_PIP, cl))
			exit(EXIT_FAILURE);
		shell_loop(tree->left, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	p.r_pid = fork();
	if (p.r_pid == -1)
		return (err_msg("sh_pipe pipe fork error"), 0);
	if (!p.r_pid)
	{
		if (!fd_redirection(&p, RES_IN | RED_PIP, cl))
			exit(EXIT_FAILURE);
		shell_loop(tree->right, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	return (wait_pipe(p), 0);
}