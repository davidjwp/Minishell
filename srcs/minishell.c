/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:34:46 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 18:08:26 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SH_functs.h"
#include "../includes/SH_structs.h"

volatile int g_signal;

//this is just to exit the program easier
int	check_input(char *input)
{
	char	*exit = "exit";

	for (int i = 0; input[i] != 0; i++)
		if (input[i] != exit[i])
			return (0);
	free(input);
	return (1);
}

//hti
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

t_fds	*init_fds(void)
{
	t_fds	*in;
	t_fds	*out;

	in = malloc(sizeof(t_fds *));
	out = malloc(sizeof(t_fds *));
	in->fd = dup(STDIN_FILENO);
	out->fd = dup(STDOUT_FILENO);
	in->next = out;
	out->next = in;
	return (in);
}

//might not need the rl_redisplay function 
int	sh_init(char *input, t_env *sh_env, t_cleanup *cl)
{
	// rl_redisplay();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	cl->fds = init_fds();
	cl->env = sh_env;
	cl->tree = parser(input);
	cl->input = input;
	if (cl->tree == NULL)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_env		*sh_env;
	t_cleanup 	*cl;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	sh_env = cr_env(env);
	cl = malloc(sizeof(t_cleanup));
	while (42)
	{
		input = readline(PROMPT);//fon't forget to free that
		if (sh_init(input, sh_env, cl))
		{
			if (check_input(input))
				return (clean_up(cl, CL_FDS | CL_HIS), exit(EXIT_SUCCESS), 0);
			if (input && *input)
				add_history(input);
			shell_loop(cl->tree, sh_env, cl);
		}
	}
	(void)ac, (void)av;
	return (1);
}

// void	exe_builtin(t_astn *tree, int type)
// {
// 	if (type == ECHO)
// 		return (built_in_cd());
// 	else if (type == CD)

// 	else if (type == PWD)

// 	else if (type == EXPORT)

// 	else if (type == UNSET)

// 	else if (type == ENV)

// 	else if (type == EXIT)

// }

int	shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	if (tree == NULL)
		return (input_enter(), 0);
	if (tree->type == PIPE)
		sh_pipe(tree, sh_env, cl);
	else if (!(tree->type % 4))
		sh_red(tree, sh_env, cl);
	else
		execute(tree, sh_env, cl);
	if (tree == cl->tree)
		clean_up(cl, CL_FDS | CL_TRE | CL_INP);
	return (1);
}

	// else if (tree->token[0]->type % 11)
	// 	exe_builtin(tree, tree->token[0]->type);