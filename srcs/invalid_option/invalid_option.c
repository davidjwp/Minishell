/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_option.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:19:25 by rmohamma          #+#    #+#             */
/*   Updated: 2023/11/03 19:30:49 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

/* base on the subject i dont need to handle (\ ; ! and -) i did it by the mistake */
int	is_valid_option(char *cmd_name, char *name)
{
    if (ft_strchr(name, '!'))
	{
		error_event(ft_strchr(name, '!'));
		return 0;
	}
	if (char_check(*name, '-'))//it returns pointer
	{
		error_invalid_name(ft_strchr(name, '-'), cmd_name, 2);
		return (0);
	}
	return (1);
}