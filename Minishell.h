/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 21:12:56 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/15 21:12:57 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT	"$> "
# define KEYWORD	0
# define ARGUMENT	1
# define OPERATOR	2
# define QUOTED		3
# define SPECIAL	4
//no comment, substitutions, variables or separators


volatile int	g_signal;

typedef struct parsetreenode{
	int						type;
	int						position;
	int						chnum;
	int						charnum;//this might not be useful
	char					*string;
	struct parsetreenode	*parent;
	struct parsetreenode	**child;
}			t_ptn;

void		err_msg(char *msg);
char		**ft_split(char *s, char c);
int			parser(char *input);

#endif