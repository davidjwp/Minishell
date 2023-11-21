/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/10 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/SH_functs.h"
#include "../includes/SH_structs.h"

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	ptr_size;

	ptr_size = (int)(nmemb * size);
	if (size != 0 && nmemb != (size_t)ptr_size / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (ptr_size--)
		ptr[ptr_size] = 0;
	return (ptr);
}

void	print_sh_env(t_env *sh_env)
{
	FILE	*_file;
	t_env	*tmp;

	tmp = sh_env;
	_file = fopen("sh_env_file", "w+");
	fprintf(_file, "%s=%s\n", sh_env->name, sh_env->value);
	sh_env = sh_env->next;
	while (sh_env != tmp)
	{
		fprintf(_file, "%s=%s\n", sh_env->name, sh_env->value);
		sh_env = sh_env->next;
	}
	fclose(_file);
}

void	input_enter(void)
{
	g_signal = 0;
	rl_replace_line("", 0);
	rl_redisplay();
}
