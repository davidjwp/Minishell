/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctest.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:39:46 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/30 15:39:47 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct	s_struct{
	int	struct_member;
	char	char_member;
}				t_struct;

t_struct	ret_struct(void)
{
	t_struct	st;

	st.struct_member = 2;
	st.char_member = "sup'";
	return (st);
}

int	main(void)
{
	if (ret_struct().struct_member == 2)
		printf ("lol it works\n");
	return (0);
}
