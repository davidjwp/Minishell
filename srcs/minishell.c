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

//TEST FUNCTIONS

//this is just to exit the program easier
int	check_input(char *input)
{
	char	*exit = "exit";

	if (!*input)
		return (0);
	for (int i = 0; exit[i] != 0; i++)
		if (input[i] != exit[i])
			return (0);
	return (1);
}

void	print_exit(int status)
{
	printf("exit:%d\n", status);
}


/*
* sh_init will initialize the global data structure for the shell
* the fds in order to always keep the original stdios in case of pipes or redir
* the tree is created and parsed here and the status set to 0 on the first pass
* the data structure contains the input, envs, tree, status and fds 
*/
int	sh_init(char *input, t_env *sh_env, t_cleanup *cl)
{
	static int	passes;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	cl->fds = init_fds();
	cl->env = sh_env;
	cl->input = input;
	cl->pids = NULL;
	if (!passes)
		cl->status = 0;
	cl->tree = parser(input, cl);
	passes += 1;
	if (cl->input && *cl->input)
		add_history(cl->input);
	if (cl->tree == NULL)
		return (clean_up(cl, CL_FDS | CL_INP | CL_FDS), 0);
	return (1);
}

/*
* the main function which checks for the availability of the stdio fds
* then the shell env consisting of the env being passed to the main function
* then the main loop where the global data structure is created and the
* shell_loop
*/
int	main(int ac, char **av, char **env)
{
	char		*input;
	t_env		*sh_env;
	t_cleanup	*cl;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))//don't think i really need that
		return (0);
	sh_env = cr_env(env);
	if (sh_env == NULL)
		return (0);
	cl = malloc(sizeof(t_cleanup));
	if (cl == NULL)
		return (err_msg("cl malloc fail"), 0);
	while (42)
	{
		input = readline(PROMPT);
		if (sh_init(input, sh_env, cl))
		{
			if (check_input(input))
				return (clean_up(cl, CL_ALL), exit(EXIT_SUCCESS), 1);
			shell_loop(cl->tree, sh_env, cl);
		}
		print_exit(cl->status);
	}
	return ((void)ac, (void)av, 1);
}

//void	exe_builtin(t_astn *tree, int type)
//{
//	if (type == ECHO)
//		return (built_in_cd());
//	else if (type == CD)
//		return (built_in_);
//	else if (type == PWD)

//	else if (type == EXPORT)

//	else if (type == UNSET)

//	else if (type == ENV)

//	else if (type == EXIT)
//;
//}

int	sh_pipe(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	t_pipe	p;

	if (pipe(p.pipe_fd) == -1)
		return (err_msg("sh_pipe pipe error"), 0);
	p.l_pid = fork();
	if (p.l_pid == -1)
		return (err_msg("sh_pipe fork error"), 0);
	if (!p.l_pid)
	{
		if (!fd_redirection(&p, RED_PIP | RES_OUT, cl))
			exit(EXIT_FAILURE);
		//if (!(tree->left->token[0]->type % 11))
		//	exe_builtin(tree, tree->token[0]->type);
		//else
			execute(tree->left, sh_env, cl);
		exit(EXIT_SUCCESS);
	}
	wait(&cl->status);
	dup2(p.pipe_fd[0], STDIN_FILENO);
	close_pipe(p.pipe_fd);
	shell_loop(tree->right, sh_env, cl);
	return (dup2(get_fd(STDI, cl->fds), STDIN_FILENO), 0);
}

/*
* the main shell loop which redirects or pipes the output in order of the tree
* being recursively called
*/
int	shell_loop(t_astn *tree, t_env *sh_env, t_cleanup *cl)
{
	if (tree == NULL)
		return (input_enter(), clean_up(cl, CL_FDS | CL_INP), 0);
	if (tree->type == PIPE)
		sh_pipe(tree, sh_env, cl);
	else if (!(tree->type % 4))
		sh_red(tree, sh_env, cl);
	else if (is_herd(tree->token))
		exe_herd(tree, sh_env, cl);
	else
		execute(tree, sh_env, cl);
	if (tree == cl->tree)
		clean_up(cl, CL_FDS | CL_TRE | CL_INP);
	return (1);
}

	//else if (!(tree->token[0]->type % 11))
	//	exe_builtin(tree, tree->token[0]->type);
