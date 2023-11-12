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
#include <stdio.h>
#include <stdbool.h>

bool	func(int *index)
{
	while (*index < 10)
		*index++;
	return (true);
}

void	func2(int *index, bool value)
{
	if (value == true)
		printf ("%i\n", *index);
}

int	main(void)
{
	int	i;

	i = 0;
	func2(&i, func(&i));
	return (0);
}
