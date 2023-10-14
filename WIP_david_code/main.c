/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:12:25 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/15 21:12:26 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	check_exit(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] != "exit"[i])
			return (0);
		i++;
	}
	free(input);
	return (1);
}

int main(int argc, char **argv)
{
	char	*input;

	rl_clear_history();
	(void)argc;
	(void)argv;
	while ("REPL Read-Eval-Print-Loop")
	{
		input = readline(PROMPT);
		if (!input || check_exit(input))
			return (printf ("exiting ...\n"), 0);
		parser(input);
		printf ("%s\n", input);
		free(input);
	}
	return (1);
}

/*
*	the ctrl-D sends a EOF to input, which is read by the shell and when shell gets to EOF
*	it exits, it is also considered a END OF TRANSMISSION signal for end of stream 
*/