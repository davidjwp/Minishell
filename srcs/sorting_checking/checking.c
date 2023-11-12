/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:49:38 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/01 14:31:17 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

int char_check(char c1, char c2)
{
	if (!c1 || !c2)
		return (0);
	if (c1 == c2)
		return 1;
	else
		return 0;//when there is'=' returns 1,else returns 0
}

int	check_quotes(char *s)
{
	int	i;
	int	quote_flag;

	i = 0;
	while (s[i])
	{
		
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote_flag = s[i];
			i++;
			while (s[i] && s[i] != quote_flag)
				i++;
			if (s[i] == '\0')
				return (0);//does not closed
		}
		++i;
	}
	return (1);//it is closed
}
