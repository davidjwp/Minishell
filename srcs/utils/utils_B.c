/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_A.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:27:48 by djacobs           #+#    #+#             */
/*   Updated: 2023/11/24 18:58:51 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/SH_functs.h"
#include "../../includes/SH_structs.h"

void	input_enter(void)
{
	g_signal = 0;
	rl_replace_line("", 0);
	rl_redisplay();
}

int	get_fd(t_fds *fds)
{
	t_fds	*tmp;

	tmp = fds;
	while (tmp->std != STDI && tmp->next != fds)
		tmp = tmp->next;
	return (tmp->fd);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	src_lenght;
	unsigned int	i;

	i = 0;
	src_lenght = ft_strlen(src);
	if (!src || !dst)
		return (src_lenght);
	if (size)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_lenght);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (*s1 == *s2 && n - 1)
	{
		s1++;
		s2++;
		n--;
	}
	if ((*s1 - *s2) == -128)
		return (1);
	return (*s1 - *s2);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			dst_lenght;
	size_t			src_lenght;
	unsigned int	index;

	index = 0;
	dst_lenght = ft_strlen(dst);
	src_lenght = ft_strlen(src);
	if (size <= dst_lenght)
		return (src_lenght + size);
	while (src[index] && index < size - dst_lenght - 1)
	{
		dst[dst_lenght + index] = src[index];
		index++;
	}
	dst[dst_lenght + index] = '\0';
	return (dst_lenght + src_lenght);
}

