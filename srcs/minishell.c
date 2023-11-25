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

	if (!*input)
		return (0);
	for (int i = 0; input[i] != 0; i++)
		if (input[i] != exit[i])
			return (0);
	return (1);
}

//might not need the rl_redisplay function 
int	sh_init(char *input, t_env *sh_env, t_cleanup *cl)
{
	static int	passes;

	// if (!*input)
	// 	return (free(input), 0); 
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	cl->fds = init_fds();
	cl->env = sh_env;
	cl->input = input;
	if (!passes)
		cl->status = 0;
	cl->tree = parser(input, cl);
	passes += 1;
	if (input && *input)
		add_history(input);
	if (cl->tree == NULL)
		return (clean_up(cl, CL_FDS | CL_INP | CL_FDS), 0);
	return (1);
}

void	print_exit(int status)
{
	printf("exit:%d\n", status);
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_env		*sh_env;
	t_cleanup	*cl;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (0);
	sh_env = cr_env(env);
	cl = malloc(sizeof(t_cleanup));
	while (42)
	{
		input = readline(PROMPT);
		if (sh_init(input, sh_env, cl))
		{
			if (check_input(input))
				return (clean_up(cl, CL_ALL), exit(EXIT_SUCCESS), 0);
			shell_loop(cl->tree, sh_env, cl);
		}
		print_exit(cl->status);
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
		return (input_enter(), clean_up(cl, CL_FDS | CL_INP), 0);
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


/*
==83447== HEAP SUMMARY:
==83447==     in use at exit: 205,069 bytes in 250 blocks
==83447==   total heap usage: 621 allocs, 371 frees, 237,431 bytes allocated
==83447==
==83447== 48 (16 direct, 32 indirect) bytes in 1 blocks are definitely lost in loss record 26 of 80
==83447==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==83447==    by 0x10CC71: init_fds (fds.c:127)
==83447==    by 0x10C177: sh_init (minishell.c:39)
==83447==    by 0x10C275: main (minishell.c:64)
==83447==
==83447== 66 bytes in 1 blocks are definitely lost in loss record 27 of 80
==83447==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==83447==    by 0x489DBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==83447==    by 0x487B694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==83447==    by 0x4885D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==83447==    by 0x10C25A: main (minishell.c:63)
==83447==
==83447== 806 (40 direct, 766 indirect) bytes in 1 blocks are definitely lost in loss record 43 of 80
==83447==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==83447==    by 0x10AA86: create_ast (create_ast.c:109)
==83447==    by 0x10C766: parser (parser.c:87)
==83447==    by 0x10C1BE: sh_init (minishell.c:44)
==83447==    by 0x10C275: main (minishell.c:64)
==83447==
==83447== LEAK SUMMARY:
==83447==    definitely lost: 122 bytes in 3 blocks
==83447==    indirectly lost: 798 bytes in 26 blocks
==83447==      possibly lost: 0 bytes in 0 blocks
==83447==    still reachable: 204,149 bytes in 221 blocks
==83447==         suppressed: 0 bytes in 0 blocks
==83447== Reachable blocks (those to which a pointer was found) are not shown.
==83447== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==83447==
==83447== For lists of detected and suppressed errors, rerun with: -s
==83447== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
*/