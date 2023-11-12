/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:14:06 by rmohamma          #+#    #+#             */
/*   Updated: 2023/10/31 14:37:21 by rmohamma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/structures.h"

char *get_next_str(const char *str, char c)
{
	char *next_str;

	next_str = ft_strchr(str, c);//it returns a pointer to the place of =
    //printf("\nnext_str %s\n", next_str);
	if (next_str)//we have $
	{
        next_str++;
        //printf("next_str after $ %s\n", next_str);
        if (*next_str)//we have new string
		{
            *(--next_str) = '\0';//we replace = with \0
            //printf("new str after null %s\n", str);
            //printf("return nex_str %s\n", ++next_str);
		    return (++next_str);//we have just next_str
        }
        else // we have only $ and we return $
        {
            //printf("we have only $ and we return %s\n", --next_str);
            *(--next_str) = '\0';
            return ("$");
        }
	}
    else
    {
       // printf("return null %s\n", --next_str);
        return (NULL);//null when it does not find $ or we have null after $
    }
	    
}

// Function to replace environment variables
void ft_dollar (char *str, t_env *fake_env)
{ 
    char *next_str;
    //printf("i'm in the fiunction\n");
    //printf("str is %s\n", str);
    if (*str == '$')//******* do i have to verify here echo jhfgjh$USER
        str++;
    if(*str)
    {
        //printf("str is %s\n", str);
        next_str = get_next_str(str, '$');//or it finds $ or it does not find it
        //printf("next_str %s\n", next_str);
        //printf("str after next_str is %s\n", str);

        //printf("fake_env %p\n", fake_env->var_name);
        char *value = find_env_value(str, fake_env);
        //printf("my str is env_variable or not %s\n", value);
        if (value)
            ft_putstr(value);
        // else
        //     ft_putstr(str);
        if (next_str)
            ft_dollar(next_str, fake_env);
    } 
    else
        ft_putstr("$");
}

