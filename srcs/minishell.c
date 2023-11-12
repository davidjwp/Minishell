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

extern volatile int g_signal;

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_env	*sh_env;
	t_exe	exe;

	if (ac != 1 || av[1] || !isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	sh_env = cr_env(env);
	while (42)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ctrl_c);
		input = readline(PROMPT);
		if (input && *input)
			add_history(input);
		exe.pid = fork();
		if (exe.pid == -1)
			return (err_msg("main fork fail"), 0);
		if (!exe.pid)
			if (!shell_loop(parser(input), sh_env))//have to check for exit builtin because she's doing something that i don't understand
				return (0);
		wait(exe.status);
	}
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

//executor
int	shell_loop(t_astn *tree, t_env *sh_env)
{
	// static int	pass;not using that right now
	int	res;

	if (tree == NULL)
		return (input_enter(), 0);
	if (tree->type == PIPE)
		sh_pipe(tree, sh_env);
	else if (!(tree->type % 4))
		sh_red(tree, sh_env);
	else if (tree->token[0]->type % 11)
		execute(tree, sh_env)
	// else
	// 	exe_builtin(tree, tree->token[0]->type);
	return (1);
}

void	input_enter(void)
{
	g_signal = 0;
	rl_replace_line("", 0);
	rl_redisplay();
}
