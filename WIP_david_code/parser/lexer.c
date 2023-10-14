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

void	free_sym_node(t_astnode *node)
{
	free(node->token);
	free(node->token[0]);
	free(node->token[0]->content);
	free(node);
}

/*
*	creates the symbolic AST node with it's corresponding type between a pipe
*	or redirections, children are given outside the function 
*/
t_astnode*	create_ast_node(const char *input, size_t *i, t_astnode *p, int t)
{
	t_astnode	*node;
	size_t		len;

	len = 0;
	node = (t_astnode *)malloc(sizeof(t_astnode));
	if (node == NULL)
		return (NULL);
	node->token = malloc(sizeof(t_token *) * 1);//THIS IS NOT FREED
	node->token[0] = malloc(sizeof(t_astnode *));
	node->token[0]->content = get_content(input, i, &len);
	node->type = t;
	node->parent = p;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	init_node(t_astnode *node, int nbr, int *error)
{
	node->type = COMD;
	node->token = (t_token **)malloc(sizeof(t_token) * (nbr + 1));
	if (node->token == NULL)
		return (free(node), *error = 1, err_msg(AST_CN_ERR), 0);
	node->token[nbr] = NULL;
	node->left = NULL;
	node->right = NULL;
	return (1);
}

/*
*	creates the COMMAND node which holds every token 
*	of the corresponding command in the input, each token is separated by
*	type instead of separators, so are builtins if detected so each token
*	has it's precise type
*/
t_astnode*	ast_cmd_node(const char *input, size_t *index, int nbr, int *error)
{
	t_astnode	*node;
	int			i;

	i = 0;
	if (!nbr)
		return (NULL);
	node = malloc(sizeof(t_astnode));
	if (node == NULL)
		return (*error = 1, err_msg(AST_CN_ERR), NULL);
	if (!init_node(node, nbr, error))
		return (NULL);
	while (nbr != 0)
	{
		node->token[i] = (t_token *)malloc(sizeof(t_token));
		if (node->token[i] == NULL)
			return (free_tokens(node->token, i), free(node), *error = 1, NULL);
		node->token[i] = get_token(input, index, node->token[i]);
		if (node->token[i] == NULL)
			return (free_tokens(node->token, i), free(node), *error = 1, NULL);
		nbr -= 1;
		i++;
	}
	return (node);
}

t_astnode*	ast_sym_node(const char *input, size_t *i, t_astnode *parent)
{
	t_astnode	*node;
	t_astnode	*right;
	t_astnode	*left;
	int			error;

	error = 0;
	left = ast_cmd_node(input, i, nbr_token(&input[*i]), &error);
	if (error)
		return (NULL);
	node = create_ast_node(input, i, parent, type(input, *i));
	if (node == NULL)
		return (free_cmd_node(left), NULL);
	right = ast_cmd_node(input, i, nbr_token(&input[*i]), &error);
	if (error)
		return (free_cmd_node(left), free_cmd_node(right), NULL);
	right->parent = node;
	left->parent = node;
	node->left = left;
	node->right = right;
	return (node);
}

/*
make sure that index is on a redirection 
t_astnode	ast_red_node(char *input, size_t *i, int *error)
{
	t_astnode	*node;

	node = malloc(sizeof(t_astnode));
	if (*error = 1, NULL)
	node->token[0] = malloc(sizeof(t_tokens));
	if (node->token[0] == NULL)
		return (*error = 1, free(node), NULL);
	node->token[0]->content = get_content(input, i);
	if (node->token[0]->content == NULL)
		return (*error = 1, free(node), free(node->token[0]), NULL);
	return (node);
}
*/

t_astnode	*create_ast(const char *input, size_t *index, t_lus utl, t_astnode *parent)
{
	t_astnode	*cmd;
	t_astnode	*node;

	cmd = ast_cmd_node(input, index, nbr_token(&input[*index]), &utl.error);
	if(type(input, index) == PIPE)
	{
		node = create_ast(input, index, (t_lus){0, 0, 0}, \
		ast_sym_node(input, index, cmd));
		cmd->type = PIPE;
	}
	else	
		cmd = cmd->left;
	if (utl.error)
		return (NULL);
		// node = create_ast(input, index, (t_lus){0, 0, 0});
	return (cmd);
}

/*
*	if there is a pipe then check if there is also a redirection, if there is a redirection then 
*	create a command node, else if there is no redirection then create a command node 
*	
*/
//kind off recursive because of pipes, but if no pipes there is no need
// t_astnode	*create_ast(char *input, size_t *index, t_lus utl)
// {
// 	t_astnode	*node;

// 	node = (t_astnode *)malloc(sizeof(t_astnode *));
// 	if (node == NULL)
// 		return (NULL);
// 	while (input[*index] != 0)
// 	{
// 		utl.r = input_red(&input[*index]);
// 		utl.p = input_pipe(&input[*index]);
// 		if ((utl.r && utl.r < utl.p) || (!utl.p && utl.r))//not sure about that
// 			node->left = ast_sym_node(input, index, node);
// 		if ((utl.p && utl.p < utl.r) || (!utl.r && utl.p))//could be a problem if not else but can't figure how it could be
// 		{
// 			node->left = ast_cmd_node(input, index, nbr_token(&input[*index]), &utl.error);
// 			if (utl.error)
// 				return (NULL);
// 			node->right = create_ast(input, index, (t_lus){input_red(&input[*index]), input_pipe(&input[*index]), 0});
// 			if (node->right == NULL)
// 				return (free_cmd_node(node->left), NULL);
// 			return (node->type = PIPE, node);
// 		}
// 		else
// 			node = ast_cmd_node(input, index, nbr_token(&input[*index]), &utl.error);
// 		// arrange_ast(node, utl.r, utl.p);
// 	}
// 	return (node);
// }

t_astnode	*free_main1(t_astnode *node)
{
	for (int i = 0; node->token[i] != NULL; i++)
		free(node->token[i]->content);
	free(node->token);
	node = node->parent;
	free(node->left);
	node->left = NULL;
	return (node);
}

char	*print_type(int type)
{
	switch (type)
	{
		case QUOT:
			return ("QUOTES");
		case EXST:
			return ("EXSTAT");
		case APRD:
			return ("APREDIR");
		case HERD:
			return ("HEREDOC");
		case PIPE:
			return ("PIPE");
		case OPER:
			return ("OPERATOR");
		case COMD:
			return ("COMMAND");
	}
	return ("NULL");
}

void	print_node(t_astnode *node)
{
	
	printf ("{node type: %s\n", print_type(node->type));
	printf ("node tokens: ");
	if (node->type == COMD){
		for (int i = 0; node->token[i]->content != NULL; i++){
			printf ("token %i-{ %s } ", i, node->token[i]->content);
			free(node->token[i]->content);
		}
		printf ("}\n");
	}
	if (node->left != NULL)
		print_node (node = node->left);
	else if (node->right != NULL)
		print_node (node = node->right);
}

int	main(int argc, char *argv[], char *env[])
{
	char	input[] = "cat << EOF > file | wc -c | tr =d "" > file2";
	size_t		index = 0;

	(void)argc;
	(void)argv;
	(void)env;
	t_astnode	*astroot;// = create_ast(input, &index, (t_lus){0, 0, 0});
	t_astnode	*current_node = astroot;
	print_node (current_node);
	return 0;
}

//++++++++++++++++++++++++++++++++++++TESTS


//test main
// int	main(void)
// {
// 	char	*input = "cat << EOF > file | wc -c |tr -d "" > file2";
// 	char	*last;
// 	// t_tlst	**lst;

// 	int	i = 0;
// 	int	y = 0;
// 	int	len;
// 	while (input[i] != 0)
// 	{
// 		len = 0;
// 		while (type(input[i] == SEPARATOR))
// 			i++;
// 		while (type(input[i] != SEPARATOR)){
// 			i++;
// 			len++;
// 		}
// 	}
// 	last = malloc(sizeof(char) * (len + 1));
// 	last[len + 1] = 0;
// 	i -= len;
// 	while (input[i])
// 		input[i++] = last[y++];
// 	*lst = lexer(input);
// 	for (int i = 0; !cmp((*lst)[i].token->content, last); i++){
// 		printf ("%s (%s)", print_type((*lst)[i].token->type));
// 		free((*lst)[i].token->content);
// 		free((*lst)[i].token);
// 		*lst = (*lst)[i].next;
// 	}
// 	free(last);
// }

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