/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:43:32 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/02 11:00:15 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

void	putnsplit(char *split, char *env, int n)
{
	int	i;

	i = 0;
	while (env[i] && i < n)
	{
		split[i] = env[i];
		i++;
	}
}

char	**split_env(char *env)
{
	char	**split;
	int		len;

	len = 0;
	split = malloc(sizeof(char *) * 3);
	while (env[len] && env[len] != '=')
		len++;
	split[0] = ft_calloc((len + 1), sizeof(char));
	putnsplit(split[0], env, len);
	split[1] = ft_calloc(ft_strlen(&env[len + 1]) + 1, sizeof(char));
	putnsplit(split[1], &env[len + 1], ft_strlen(&env[len + 1]));
	split[2] = NULL;
	return (split);
}

//free_split might free name and value
t_env	*env_node(char *env)
{
	t_env	*node;
	char	**split;

	split = split_env(env);
	if (split == NULL)
		return (NULL);
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (free_split(split), NULL);
	node->name = split[0];
	node->value = split[1];
	node->cl = split;
	node->next = NULL;
	return (node);
}

t_env	*cr_blank_env(void)
{
	t_env	*node;
	char	*buf;
	char	**split;
	char	*pwd;

	buf = getcwd(NULL, 0);
	if (buf == NULL)
		return (err_msg("getcwd fail"), NULL);
	pwd = ft_calloc(ft_strlen(buf) + 5, sizeof(char));
	if (pwd == NULL)
		return (free(buf), err_msg("dest malloc fail"), NULL);
	ft_strcat(pwd, "PWD=");
	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (free(buf), free(pwd), err_msg("crbe malloc fail"), NULL);
	ft_strcat(pwd, buf);
	split = ft_split(pwd, '=');
	free(buf);
	free(pwd);
	node->cl = split;
	node->name = split[0];
	node->value = split[1];
	node->next = node;
	return (node);
}

/*
*	creates the env list to be used in the shell
*	each list will have to be reconstructed into an array of string
*	before execution to serve as execution environment
*/
t_env	*cr_env(char **env)
{
	t_env	*sh_env;
	t_env	*tmp;
	int		i;

	if (!*env)
		return (cr_blank_env());
	i = 0;
	sh_env = env_node(env[i]);
	if (sh_env == NULL)
		return (NULL);
	tmp = sh_env;
	while (env[++i] != NULL)
	{
		sh_env->next = env_node(env[i]);
		if (sh_env->next == NULL)
			return (sh_env->next = tmp, free_env(sh_env), NULL);
		sh_env = sh_env->next;
	}
	sh_env->next = tmp;
	sh_env = sh_env->next;
	return (sh_env);
}
