/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:33:17 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 11:30:08 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/******************************** to verify **********************************/
//
//
//
/*****************************************************************************/

static int no_arg_set(t_one_token *one_cmd, t_env *fake_env);
static int	handle_tilde_and_dash(t_one_token *dir, t_env *fake_env, t_env *second_env);
//static int	handle_tilde_and_dash(t_one_token *dir, t_env *fake_env);
static char	*create_path(t_one_token *head, t_env *curr);
static int	change_directory(char *path, t_env *fake_env, t_one_token *one_cmd);
static int	specific_path_2(t_env *curr_env, t_env *second_env, char *str);

//int	built_in_cd(t_one_token *token, t_env *fake_env)
int	built_in_cd(t_one_token *token, t_env *fake_env, t_env *second_env)// because of cd~ and unset HOME
{
	int			b_status;
	char		*path;
	t_one_token	*dir;

	dir = token->next;//directory
	path = NULL;
	b_status = -42;
	if (token && token->next && token->next->next)
	{
		error_many_args(token->str);
		return exit_status;
	}
	b_status = no_arg_set(dir, fake_env);// 0 or 1
	while (dir)
	{
		//b_status = handle_tilde_and_dash(dir, fake_env);
		b_status = handle_tilde_and_dash(dir, fake_env, second_env);// 0 or 1
		if (b_status == -42)// when we have absolute path
		{
			path = create_path(dir, fake_env);
			if (path)
				b_status = change_directory(path, fake_env, dir);// 0 or 1
		}
		dir = dir->next;
	}
	free(path);
	//return (exit_status);
	return (b_status);// 0 or 1
}

static int no_arg_set(t_one_token *one_cmd, t_env *fake_env)
{
	int ret;

	ret = -42;
	if (!one_cmd)
	{
		if(!find_env_value_cd("HOME", fake_env))//0 when we don't have variable 
		{
			ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
			return (exit_status = 1);
		}
		else// cd goes to the home dir
			ret = specific_path(fake_env, "HOME");// 0 or 1
	}
	return (ret);// exit_status 0 or 1
}
//static int	handle_tilde_and_dash(t_one_token *head, t_env *fake_env)
static int	handle_tilde_and_dash(t_one_token *dir, t_env *fake_env, t_env *second_env)
{
	int	ret;

	ret = -42;
	if (!ft_strcmp(dir->str, "~"))
	{
		//ret = specific_path(second_env, "HOME");// 0 or 1
		ret = specific_path_2(fake_env, second_env, "HOME");
	}
	else if (!ft_strcmp(dir->str, "-"))
	{
		ret = specific_path(fake_env, "OLDPWD");// 0 or 1
		if (!ret)
			print_pwd(fake_env, "PWD");
	}
	return (ret);
}

static char	*create_path(t_one_token *dir, t_env *fake_env)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	if (dir->str[0] == '/')
		path = ft_strdup(dir->str);
	else
	{
		while (fake_env)
		{
			if (!ft_strcmp(fake_env->var_name, "PWD"))// when we found the dir
			{
				tmp = ft_strjoin(fake_env->var_value, "/");
				path = ft_strjoin(tmp, dir->str);
			}
			fake_env = fake_env->next;
		}
		free(tmp);
	}
	return (path);//is null when we did not find the directory
}

static int	change_directory(char *path, t_env *fake_env, t_one_token *one_cmd)
{
	int	ret;

	ret = chdir(path);//0,1
	if (ret)
		error_dir(one_cmd->str, "(change_directory_fun)cd");
	else
	{
		change_path(fake_env);
		exit_status = 0;
	}	
	return (exit_status);
}
/*** in need this function because in bash unset HOME + cd + pwd we have home adress ***/
static int	specific_path_2(t_env *curr_env, t_env *second_env, char *str)
{
	char	*value;
	int		result;

	value = find_env_value_cd(str, second_env);
	if (!value)//when we dont have this env's variable
		return (exit_status = 1);// exit_status = 1 // error
	result = chdir(value);//change the current working directory (0 or -1)
	if (result)//-1 when we dont have a such directory
	{
		error_dir(value, "(specific_path_fun)cd");
		return (exit_status = 1);// exit_status = 1 // error
	}
	change_path(curr_env);
	return (exit_status = 0);// exit_status = 0 // well done
}