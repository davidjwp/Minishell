/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:28:23 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/19 16:28:24 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Minishell.h"

int	get_type(char *token)
{
	int	i;

}



int	plant_tree(t_ptn *tokens)
{

}

int	create_tree(char **tokens_s, int tokens_n, t_ptn *tree)
{
	tree->
}

/*
*	start out by splitting the input and create a root for the tree 
*
*
*/
int	parser(char	*input)
{
	char	**tokens_s;
	t_ptn	*tokens;
	int		tokens_n;
	int		i;

	i = 0;
	if (!input)
		return (0);
	tokens_s = tokenize(input, &tokens_n, 0);
	if (!tokens_s)
		return (free(input), 0);
	tokens = (t_ptn *)malloc(sizeof(t_ptn) * tokens_n);
	while (i < tokens_n)
	{
		tokens[i].string = tokens_s[i];
		tokens[i].position = tokens_n;
		tokens[i].type = get_type(tokens[i].string);
		tokens[i].child = NULL;
		tokens[i].parent = NULL;
		i++;
	}
	free_tokens(tokens_s);
	plant_tree(tokens);
	return (1);
}

/*
*	list of the special characters that are explicitily asked in the subject
*	anything not asked is not required.
*
*	(') single quotes which do no interpretation
*	(") double quotes which only interpret $ for variables
*	($) dollar sign for variables including env
*	(>) output redirection
*	(<) input redirection
*	(<<) heredoc with delimiter and read until a line containing the delimiter
*		is seen, does not have to update history
*	(>>) output redirection but appends the text instead of writing over
*	(|) pipes
*	($?) this expands to the exit status of the last executed foreground
*	pipeline meaning what's left in the pipe if it has anything in it
*/

// typedef struct parsetreenode{
// 	int						type;
// 	int						position;
// 	int						chnum;
// 	int						charnum;
// 	char					*string;
// 	struct parsetreenode	*parent;
// 	struct parsetreenode	**child;
// }			t_ptn;

/*
*	The fundamental difference between single single quote and double quote
*	is in how they treat variables, single text does no interpretation for 
*	variables, while double quotes does
*
*	In Minishell unclosed quotes are not handled, but should still give an
*	error if encountered, there is also no escape character and thus the only
*	special character interpretation is done in double quotes where only one 
*	special character is handled, the $ for variables
*
*/

/*
In Bash, several characters are considered special and have specific meanings or functions. 
Here's a list of some common special characters in Bash:

$ " ' # ! * ? [] {} ( | & > $() bonus && || 

1. **`$`**: Denotes the start of a variable name. For example, `$VAR` represents the value 
of the variable `VAR`.

2. **`"`**: Double quotes are used for enclosing strings that allow variable substitution 
and command substitution. For example, `"$VAR"` expands the variable `VAR`.

3. **`'`**: Single quotes are used for enclosing strings that treat all characters as 
literals, with no variable or command substitution. For example, `'$VAR'` treats `$VAR` as a literal string.

4. **`#`**: Indicates the start of a comment. Everything following `#` on the same line 
is treated as a comment and is ignored by the shell.

5. **`!`**: Used for history expansion when the `history` feature is enabled. For 
example, `!!` represents the last command executed.

6. **`*`**: Represents a wildcard character for pattern matching. For example, 
`*.txt` matches all files with a `.txt` extension in the current directory.

7. **`?`**: Represents a wildcard character for matching a single character. 
For example, `file?.txt` matches files like `file1.txt` and `fileA.txt`.

8. **`[ ]`**: Used for character classes in pattern matching. For example, 
`[abc]` matches any one of the characters `a`, `b`, or `c`.

9. **`{ }`**: Used for brace expansion. For example, `{a,b}` expands to `a` and `b`, allowing 
you to create multiple similar strings.

10. **`(` and `)`**: Used for grouping commands. For example, `(command1; command2)` runs 
`command1` and `command2` in a subshell.

11. **`|`**: Represents a pipe, used to send the output of one command as input to 
another. For example, `command1 | command2` pipes the output of `command1` to `command2`.

12. **`&`**: Used for backgrounding a command. For example, `command &` runs `command` 
in the background, allowing you to continue working in the shell.

14. **`>` and `<`**: Used for redirection. `>` redirects output to a file, and `<` 
redirects input from a file. For example, `command > output.txt` sends the output of `command` to `output.txt`.

15. **`$()` and `` ` ``**: Used for command substitution. `$()` or `` ` `` allows 
you to execute a command and capture its output. For example, `result=$(command)` stores 
the output of `command` in the variable `result`.

16. **`&&` and `||`**: Used for conditional execution. `&&` executes the command on its right 
only if the command on its left succeeds (returns a zero exit status). `||` executes the command 
on its right only if the command on its left fails (returns a non-zero exit status).

17. **`*` and `**`**: Used in globbing and extended globbing for pattern matching.

These are some of the common special characters in Bash. Understanding their meanings and uses is essential 
for working effectively in the Bash shell.
*/