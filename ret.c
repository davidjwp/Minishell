/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:05:19 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/25 18:05:20 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

typedef struct s_type{
	int	a;
	int	b;
	int	c;
}				t_type;


void	*ret()
{
	return ((void)NULL);
}

int	funct1()
{
	return (ret());
}

char	*funct2()
{
	return (ret());
}

t_type	funct3()
{
	return (ret());
}

int	main(void)
{
	t_type	s;

	funct1();
	funct2();
	funct3();
}