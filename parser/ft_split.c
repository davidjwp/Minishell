/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:05:01 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/19 19:05:06 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../Minishell.h"

void	free_split(char **var)
{
	int	i;

	i = 0;
	while (var[i] != NULL)
		free(var[i++]);
	free(var);
}

static char	*ft_word_cpy(char const *s, char c)
{
	char	*word_cpy;
	int		word_len;
	int		index;

	index = 0;
	word_len = 0;
	while (s[word_len] != c && s[word_len])
		word_len++;
	word_cpy = (char *)malloc(word_len + 1);
	if (word_cpy == NULL)
		return (err_msg("split word copy fail"), ERROR_FT_CPY);
	while (index < word_len)
	{
		word_cpy[index] = s[index];
		index++;
	}
	word_cpy[index] = '\0';
	return (word_cpy);
}

static int	ft_word_count(char const *s, char c)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			return (word_count);
		word_count++;
		while (*s != c && *s)
			s++;
	}
	return (word_count);
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		index;

	index = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof (char *) * (ft_word_count(s, c) + 1));
	if (split == NULL)
		return (err_msg("split malloc fail"), free(s), NULL);
	while (*s)
	{
		if (*s == 10 && !s[1])
			break ;
		while (*s == c && *s)
			s++;
		if (*s)
			split[index] = ft_word_cpy(s, c);
		if (split[index] == ERROR_FT_CPY)
			return (split[index] = NULL, free(s), free_split(split), NULL);
		index++;
		while (*s != c && *s)
			s++;
	}
	return (split[index] = NULL, split);
}
