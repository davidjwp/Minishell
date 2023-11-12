/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_edited.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:52:21 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 11:11:45 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"
/******************************** to verify **********************************/
//
// when in the name of my folder is space it think that there are too many
// args so it returns too many args error because my parsing is not correct!
//
/*****************************************************************************/

static void no_arg_set(t_env *fake_env);
static void execute_dir(t_one_token *dir, t_env *fake_env, t_env *second_env, char *path);
static char	*create_path(t_one_token *head, t_env *curr);
static void	change_directory(char *path, t_env *fake_env, t_one_token *one_cmd);

//int	built_in_cd_edited(t_one_token *token, t_env *fake_env)
int	built_in_cd_edited(t_one_token *token, t_env *fake_env, t_env *second_env)// because of cd~ and unset HOME
{
	char		*path;
	t_one_token	*dir;

	dir = token->next;//directory
	path = NULL;
	if (token && token->next && token->next->next)
	{
		error_many_args(token->str);
		return exit_status;
	}
    if (!dir)
	    no_arg_set(fake_env);// 0 or 1
	else
		while (dir)//cd 42-Cursus/Project_in_Progress
    	{
			execute_dir(dir, fake_env, second_env, path);
			dir = dir->next;
		}
	free(path);
	return (exit_status);// 0 or 1
}

static void no_arg_set( t_env *fake_env)
{
    if(!find_env_value_cd("HOME", fake_env))//0 when we don't have variable 
    {
        ft_putendl_fd("bash: cd: HOME not set", STDERR_FILENO);
        exit_status = 1;
    }
    else// cd goes to the home dir
        specific_path(fake_env, "HOME");// 0 or 1
}

static void execute_dir(t_one_token *dir, t_env *fake_env, t_env *second_env, char *path)
{
    if (!ft_strcmp(dir->str, "~"))
	{
		//ret = specific_path(second_env, "HOME");// 0 or 1
		specific_path_2(fake_env, second_env, "HOME");
	}
	else if (!ft_strcmp(dir->str, "-"))
	{
		specific_path(fake_env, "OLDPWD");// 0 or 1
		if (!exit_status)
			print_pwd(fake_env, "PWD");
	}
    else// when we have absolute path
    {
        path = create_path(dir, fake_env);
        if (path)
           change_directory(path, fake_env, dir);// 0 or 1
    }
}

static char	*create_path(t_one_token *dir, t_env *fake_env)
{
	char	*path;
	char	*tmp;

	path = NULL;
	tmp = NULL;
	fake_env = NULL;
	if (dir->str[0] == '/')
		path = ft_strdup(dir->str);
	else
	{
		if (getcwd(NULL, 0))
		{
			tmp = ft_strjoin(getcwd(NULL, 0), "/");
			path = ft_strjoin(tmp, dir->str);
		}
		// while (fake_env)
		// {
			
		// 	 if (!ft_strcmp(fake_env->var_name, "PWD"))// when we found the dir
		// 	 {
		// 	 	tmp = ft_strjoin(fake_env->var_value, "/");
		// 	 	path = ft_strjoin(tmp, dir->str);
		// 	 }
		// 	fake_env = fake_env->next;
		// }
		free(tmp);
	}
	//printf("pwd is %s\n", path);
	//printf("getcwd() %s\n", getcwd(NULL, 0));
	return (path);//is null when we did not find the directory
}

static void	change_directory(char *path, t_env *fake_env, t_one_token *one_cmd)
{
	int	ret;

	ret = chdir(path);//0,1
	if (ret)// for example we deleted it after or we dont have it already
		error_dir(one_cmd->str, "(change_directory_fun)cd");
	else
	{
		change_path(fake_env);
		exit_status = 0;
	}	
}

