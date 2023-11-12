/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:33:59 by rmohamma          #+#    #+#             */
/*   Updated: 2023/10/13 20:00:16 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef int	(*t_execute_ast_fun)(t_minishell *minishell, t_ntree *ast);

typedef enum e_type
{
	or = 1,
	and,
	ppipe,
	great,
	less,
	dgreat,
	dless,
	opening_parenthesis,
	closing_parenthesis,
	newline,
	word,
	error,
	ambiguous_word,
	COMPLETE_COMMAND,
	COMPOUND_COMMAND,
	LOGICAL_EXPRESSION,
	PIPELINE,
	SIMPLE_COMMAND,
	CMD_NAME,
	CMD_ARG,
	CMD_PREFIX,
	CMD_SUFFIX,
	REDIRECTION,
	OPERATOR,
	FILENAME,
	AND,
	OR,
	HERE_DOC,
	HERE_END,
}	t_type;

typedef struct s_ntree
{
	void	*data;
	t_llist	*children;
}	t_ntree;

typedef struct s_llist
{
	void			*content;
	struct s_llist	*prev;
	struct s_llist	*next;
}	t_llist;

typedef struct s_token
{
	t_type	type;
	void	*data;
}	t_token;

typedef int	(*t_execute_ast_fun)(t_minishell *minishell, t_ntree *ast);

int	execute_complete_command(t_minishell *minishell, t_ntree *ast)
{
	t_ntree *const			child = ast->children->content;
	const t_execute_ast_fun	execute_function = get_execute_function(child);

	return (execute_function(minishell, child));
}

int	execute_pipeline(t_minishell *minishell, t_ntree *ast)
{
	t_info *const	pipex_info = get_token(ast)->data;

	return (pipex(minishell, pipex_info));
}

int	execute_logical_expression(t_minishell *minishell, t_ntree *ast)
{
	t_ntree *const			lhs = ast->children->content;
	t_ntree *const			rhs = ast->children->next->content;
	const t_execute_ast_fun	lhs_execute_function = get_execute_function(lhs);
	const t_execute_ast_fun	rhs_execute_function = get_execute_function(rhs);
	int						lhs_return_status;

	lhs_return_status = lhs_execute_function(minishell, lhs);
	if (lhs_return_status == 0 && (intptr_t)get_token(ast)->data == AND)
		return (rhs_execute_function(minishell, rhs));
	else if (lhs_return_status != 0 && (intptr_t)get_token(ast)->data == OR)
		return (rhs_execute_function(minishell, rhs));
	return (lhs_return_status);
}


t_token	*get_token(t_ntree *ast)
{
	return (((t_token *)(ast->data)));
}
void	*get_execute_function(t_ntree *ast)
{
	const t_type	type = get_token(ast)->type;

	if (type == PIPELINE)
		return (execute_pipeline);
	else if (type == COMPLETE_COMMAND)
		return (execute_complete_command);
	else if (type == LOGICAL_EXPRESSION)
		return (execute_logical_expression);
	else
		return (NULL);
}



int	execute_ast(t_minishell *minishell)
{
	const t_execute_ast_fun	execute_function = \
		get_execute_function(minishell->ast);

	return (execute_function(minishell, minishell->ast));
}
