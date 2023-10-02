/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcctest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:29:08 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/22 17:29:09 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	char	*dblptr[7];
	int		i;

	i = -1;
	while (++i < 7)
		dblptr[i] = (char* [7]){"string1", "string2", "string3", "string4", "string5", "string6", "string7"}[i];
	for (int y = 0; y < 7; y++)
		printf ("%s\n", dblptr[y]);
	return (0);
}