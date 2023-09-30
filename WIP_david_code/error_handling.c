/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djacobs <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 16:48:51 by djacobs           #+#    #+#             */
/*   Updated: 2023/09/30 16:48:53 by djacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdarg.h>
# include <stddef.h>

//i can't actually use this because it makes use of va
void	*h_error(int count, ...)
{
	va_list	_valist;
	void	*_vptr;	

	va_start(_valist, count);
	if (!count)
		return (NULL);
	_vptr = va_arg(_valist, void *);
	if (_vptr == NULL)
	{
		while (count)
		{
			free((void *)free_ptr);
			free_ptr = va_arg(_valist, void *);
			count -= 1;
		}
	}
	return (NULL);
}
