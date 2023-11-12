/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:32:16 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 15:03:30 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/******************************** to verify **********************************/
//
//
//
/*****************************************************************************/

int	built_in_pwd(t_one_token *token, t_env *fake_env)
{
	char	*cwd;

	cwd = NULL;
	/***** i dont need to handle if condition part ****/
	if (token->next && !is_valid_option(token->str, token->next->str))
		return (exit_status);
/** my code works like bash when i delete a dir which already im in that dir ***/
	cwd = find_env_value_cd("PWD", fake_env);
/** but with cwd = getcwd(NULL, 0); it does not work like bash**/
	//cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("bash: cd: PWD not set", STDERR_FILENO);
		return (exit_status = 1);
	}
	else
		ft_putendl_fd(cwd, STDOUT_FILENO);
	//free(cwd);
	return (exit_status = 0);
}
// int	built_in_pwd(t_one_token *token)
// {
// 	char	*cwd;

// 	cwd = NULL;
// 	/***** i dont need to handle if condition part ****/
// 	if (token->next && !is_valid_option(token->str, token->next->str))
// 		return (exit_status);
// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		find_env_value_cd(token->str, fake_env);
// 		error_dir(cwd, "pwd");
// 		return exit_status;
// 	}
// 	ft_putendl_fd(cwd, STDOUT_FILENO);
// 	free(cwd);
// 	return exit_status;
// }