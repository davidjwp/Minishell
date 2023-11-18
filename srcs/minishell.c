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

int	check_input(char *input)
{
	char *exit = "exit"; 

	for (int i = 0; input[i] != 0; i++)
		if (input[i] != exit[i])
			return (0);
	free(input);
	return (1);
}

//might not need the rl_redisplay function 
int	sh_init(char *input, t_env *sh_env, t_cleanup *cl)
{
	rl_redisplay();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	cl->fds = NULL;
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
	print_sh_env(sh_env);//test
	cl = malloc(sizeof(t_cleanup));
	while (42)
	{
		input = readline(PROMPT);//fon't forget to free that
		if (sh_init(input, sh_env, cl))
		{
			if (check_input(input))
				return (clean_up(cl, 1), 0);
			if (input && *input)
				add_history(input);
			shell_loop(cl->tree, sh_env, cl);
		}
	}
	(void)ac, (void)av;
	return (1);
}

void	input_enter(void)
{
	g_signal = 0;
	rl_replace_line("", 0);
	rl_redisplay();
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
	static int	nb;

	nb++;
	if (tree == NULL)
		return (input_enter(), 0);
	if (tree->type == PIPE)
		sh_pipe(tree, sh_env, cl);
	else if (!(tree->type % 4))
		sh_red(tree, sh_env, cl);
	// else if (tree->token[0]->type % 11)
	// 	exe_builtin(tree, tree->token[0]->type);
	execute(tree, sh_env, cl);
	if (nb == 1)
		clean_up(cl, 0);
	return (1);
}
