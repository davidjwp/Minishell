/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_A.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/10 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

/*
*	exe_utils_A contains the following functions :
*	type(), _pipe(), _red(), cmp(), check_spec()
*/
//creates the pathname for execve while also checking for viability
char	*cr_pathname(const char *cmd, t_env *sh_env)
{
	int		i;
	char	**paths;
	char	*pathname;

	i = 0;
	if (sh_env == NULL)
		paths = ft_split(ABS_PATHS, ':');
	else
		paths = ft_split(sh_env->value, ':');
	if (paths == NULL)
		return (err_msg("ft_split Malloc fail"), NULL);
	pathname = strccat(paths[i], '/', cmd);
	while (access(pathname, X_OK) != 0 && paths[i] != NULL)
	{
		free(pathname);
		i++;
		pathname = strccat(paths[i], '/', cmd);
	}
	if (paths[i] == NULL)
		return (free_split(paths), free(pathname), err_msg("no access"), NULL);
	return (free_split(paths), pathname);
}

//convert the shell environment variables to an array of strings
char	**cr_envp(t_env *sh_env)
{
	char	**envp;
	int		len;
	int		i;

	i = -1;
	if (sh_env == NULL)
		return (envp = ft_split(ABS_PATHS, ':'));
	len = sh_envlen(sh_env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (envp == NULL)
		return (err_msg("cr_envp malloc fail"), NULL);
	envp[len] = NULL;
	while (++i < len)
	{
		envp[i] = strccat(sh_env->name, '=', sh_env->value);
		sh_env = sh_env->next;
	}
	return (envp);
}

char	**cr_args(t_token **tokens, char *pathname)
{
	char	**args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (tokens[1] == NULL)
	{
		args = malloc(sizeof(char *) * 2);
		if (args == NULL)
			return (err_msg("cr_args malloc fail"), NULL);
		args[0] = pathname;
		args[1] = NULL;
		return (args);
	}
	while (tokens[len] != NULL)
		len++;
	args = malloc(sizeof(char *) * len + 1);
	if (args == NULL)
		return (err_msg("cr_args malloc fail"), NULL);
	args[len] = NULL;
	args[0] = pathname;
	while (++i < len)
		args[i] = tokens[i]->content;
	return (args);
}

//concatenates the str2 after str1 with c in the middle
char	*strccat(const char *str1, char c, const char *str2)
{
	char	*pathname;
	int		len;
	int		y;
	int		i;

	i = -1;
	y = -1;
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	pathname = malloc(sizeof(char) * len);
	if (pathname == NULL)
		return (err_msg("cat_str2s malloc fail"), NULL);
	pathname[len] = 0;
	while (str1[++i])
		pathname[i] = str1[i];
	pathname[i] = c;
	while (str2[++y] && ++i < len)
		pathname[i] = str2[y];
	return (pathname);
}

//find the shell environment variable by name
t_env	*find_env(const char *name, t_env *sh_env)
{
	t_env	*tmp;

	tmp = sh_env;
	if (sh_env == NULL)
		return (NULL);
	if (cmp(name, sh_env->name) == true)
		return (sh_env);
	sh_env = sh_env->next;
	while (cmp(name, sh_env->name) != true && sh_env != tmp)
		sh_env = sh_env->next;
	if (sh_env == tmp)
		return (NULL);
	return (sh_env);
}