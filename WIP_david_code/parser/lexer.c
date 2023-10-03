/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:58:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/25 14:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

/*
*	('),(")			QUOTES
*	($)				SPECIAL
*	(>),(<)			OPERATOR
	(>>)			APREDIR
*	(<<)			HEREDOC
*	(|)				PIPE
*	($?)			EXSTAT
*	( ),(\t),(\n)	SEPARATOR
*/


/*
*	creates the symbolic AST node with it's corresponding type between a pipe
*	or redirections, children are given outside the function 
*/
t_astnode*	create_ast_node(char c, t_astnode *p, int type)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		return (NULL);
	node->(*token) = c;
	node->type = type;
	node->parent = p;
	node->left = NULL
	node->right = NULL;
	return (node);
}
/*
*	creates the COMMAND node which holds every token 
*	of the corresponding command in the input, each token is separated by
*	type instead of separators, so are builtins if detected so each token
*	has it's precise type
*/
t_astnode*	ast_cmd_node(char *input, int *index, int nbr, int *error)
{
	t_astnode	*node;
	int			i;

	i = 0;
	if (!nbr)
		return (NULL);
	node = (t_astnode *)malloc(sizeof(t_astnode *));
	if (node == NULL)
		return (*error = 1, NULL);
	node->type = COMMAND;
	node->token = (t_token *)malloc(sizeof(t_token) * (nbr + 1));
	if (node->token == NULL)
		return (free(node), *error = 1, NULL);
	node->token[nbr] = (t_token){0, 0, NULL};
	while (nbr != 0)
	{
		node->token[i] = (t_token){0, 0, NULL};
		node->token[i] = get_token(input, index, node->token[i].len);
		if (node->token[i] == NULL)
			return (free_tokens(node->token, i), free(node), *error = 1, NULL);
		nbr -= 1;
		i++;
	}
	return (node->left = NULL, node->right = NULL, node);
}

t_astnode*	ast_sym_node(char *input, int *i, t_astnode *parent)
{
	t_astnode	*node;
	t_astnode	*right;
	t_astnode	*left;
	int			error;

	error = 0;
	left = create_ast_command(input, i, nbr_token(&input[*i]), &error);
	if (error)
		return (NULL);
	node = create_ast_node(input[*i], parent, type(input[*i]));
	if (node == NULL)
		return (free_cmd_node(left), NULL);
	right = create_ast_command(input, i, nbr_token(&input[*i]), node);
	if (error == NULL)
		return (free_cmd_node(left), free_cmd_node(right), NULL);
	node->left = left;
	node->right = right;
	return (node);
}




// t_astnode	*create_ast(char *input, int *index, t_lus utls)
// {
// 	t_astnode	*node;

// 	node = (t_astnode *)malloc(sizeof(t_astnode *));
// 	if (node == NULL);
// 	while (input[*index])
// 	{
// 		utls.p = input_pipe(&input[*index]);
// 		utls.r = input_red(&input[*index]);
// 		if (utls.p)
// 		{
// 			if (utls.r && utls.r < utls.p)
// 				node->left = ast_sym_node(input, index, node);
// 			else
// 				node->left = ast_cmd_node(input, index, \
// 				nbr_token(&input[*index]), &utls.error);
// 			if ((utls.r && utls.r < utls.p) && node->left == NULL \
// 			|| utls.error)
// 				return (clean_ast(node), NULL);	
// 		}
// 	}
// 	return (node);
// }


//kind off recursive because of pipes, but if no pipes there is no need
t_astnode	*create_ast(char *input, int *index, t_lus utl)
{
	t_astnode	*node;

	node = (t_astnode *)malloc(sizeof(t_astnode *));
	if (node == NULL)
		return (NULL);
	while (input[*index] != 0)
	{
		utl.r = input_red(&input[*index]);
		utl.p = input_pipe(&input[*index]);
		if ((utl.r && utl.r < utl.p) || (!utl.p && utl.r))//not sure about that
			node->left = ast_sym_node(input, index, node);
		if ((utl.p && utl.p < utl.r) || (!utl.r && utl.p))//could be a problem if not else but can't figure how it could be
		{
			if ()
			node->left = create_ast_command(input, index, nbr_token(), &utl.error)
			if (utl.error)
				return (NULL);
			node->right = create_ast(input, index, input_red(&input[*index]), \
			input_pipe(&input[*index]));
			if (node->right == NULL)
				return (, NULL);
			return (, node->type == PIPE, node);
		}
		else
			node = create_ast_command(input, i, nbr_token(), &utl.error);
	}
	return (node);
}

main(int argc, char *argv[], char *env[])
{
	char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	int		index = 0;

	(void)argc;
	(void)argv;
	(void)env;
	t_astnode	*astroot = create_ast(input, &index, (t_lus){0, 0, 0});
	return 0;
}

//++++++++++++++++++++++++++++++++++++TESTS

char	print_type(int type)
{
	switch (type)
	{
		case QUOTES:
			return ("is quotes");
		case EXSTAT:
			return ("is exit status");
		case APREDIR:
			return ("is append redirection");
		case HEREDOC:
			return ("is heredoc");
		case PIPE:
			return ("is pipe");
		case OPERATOR:
			return ("is operator");
	}
}

//test main
int	main(void)
{
	char	*input = "cat << EOF > file | wc -c |tr -d "" > file2";
	char	*last;
	t_tlst	**lst;

	int	i = 0;
	int	y = 0;
	int	len;
	while (input[i] != 0)
	{
		len = 0;
		while (type(input[i] == SEPARATOR))
			i++;
		while (type(input[i] != SEPARATOR)){
			i++;
			len++;
		}
	}
	last = malloc(sizeof(char) * (len + 1));
	last[len + 1] = 0;
	i -= len;
	while (input[i])
		input[i++] = last[y++];
	*lst = lexer(input);
	for (int i = 0; !cmp((*lst)[i].token->content, last); i++){
		printf ("%s (%s)", print_type((*lst)[i].token->type));
		free((*lst)[i].token->content);
		free((*lst)[i].token);
		*lst = (*lst)[i].next;
	}
	free(last);
}

/*In GNU Bash, parse errors typically occur when the shell encounters syntax errors or invalid command structures. Here's a list of common parse errors you may encounter:

1. **Missing Command or Argument:**
   - `syntax error near unexpected token 'newline'`: Occurs when you enter a command without specifying the actual command or arguments.

2. **Misplaced Redirection Operators:**
   - `syntax error near unexpected token '>'`: Occurs when you use a redirection operator (e.g., `>`) without specifying a command or file to redirect to.

3. **Misplaced Pipe Operator:**
   - `syntax error near unexpected token '|'`: Occurs when you use the pipe operator (`|`) without specifying a command before or after it.

4. **Unclosed Quotes:**
   - `syntax error near unexpected token 'newline'` or similar messages may occur when you have unclosed single ('') or double ("") quotes.

5. **Missing Semi-Colon:**
   - `syntax error near unexpected token 'newline'` or similar messages may occur when you don't use a semi-colon (`;`) or newline to separate multiple commands on a single line.

6. **Unbalanced Parentheses or Brackets:**
   - `syntax error near unexpected token ']'` or similar messages may occur when you have unbalanced parentheses, square brackets, or curly braces.

7. **Unclosed Subshell or Command Substitution:**
   - `syntax error near unexpected token ')'` or similar messages may occur when you have an unclosed subshell or command substitution.

8. **Use of Reserved Words or Special Characters:**
   - Bash has several reserved words (e.g., `if`, `while`, `for`) and special characters (e.g., `$`, `;`) that must be used appropriately in the syntax of your commands. Using them incorrectly can result in parse errors.

9. **Use of Invalid Variable Names:**
   - `syntax error: operand expected (error token is "<invalid>")`: Occurs when you use an invalid variable name, such as starting with a number or containing special characters other than underscores.

10. **Misplaced Function Definitions:**
    - `syntax error near unexpected token '('`: Occurs when you attempt to define a function in an incorrect manner.

Please note that these are common parse errors, and the specific error messages may vary slightly depending on the version of Bash and the shell configuration. The messages will often include a description of the unexpected token or character, which can help you identify and fix the issue.*/

/*In Bash, the Ctrl-C, Ctrl-D, and Ctrl-\ keyboard shortcuts have specific actions:

1. **Ctrl-C (`^C`)**:
   - Ctrl-C is used to send an interrupt signal to the currently running foreground process in the terminal. When you press Ctrl-C, it typically stops the execution of the running command or program and returns control to the shell prompt.

2. **Ctrl-D (`^D`)**:
   - Ctrl-D is used for several purposes:
     - When typed at an empty prompt, it signals an end-of-file (EOF) character, effectively terminating the shell session. This is commonly used to exit a shell session or close a terminal.
     - When used in an interactive text input (e.g., during command line editing), it can signal the end of input for certain applications or text processes, causing them to finish processing the input.

3. **Ctrl-\ (`^\`)**:
   - Ctrl-\ is used to send a quit signal to the currently running foreground process. It's similar to Ctrl-C, but instead of terminating the process, it causes the process to terminate and generate a core dump, which can be useful for debugging.

Here's a summary of how to use these shortcuts:

- Ctrl-C: Interrupts the currently running process, stopping its execution.
- Ctrl-D:
  - At an empty prompt: Exits the current shell session.
  - During text input: Signals the end of input for certain applications.
- Ctrl-\: Sends a quit signal to the currently running process, causing it to terminate and generate a core dump.

Remember that the exact behavior of these shortcuts may vary depending on your system's configuration and the specific terminal emulator you are using.*/