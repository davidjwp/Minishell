/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:39:36 by rmohamma          #+#    #+#             */
/*   Updated: 2023/10/31 15:30:10 by rmohamma         ###   ########.fr       */
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
void ft_dollar (int i, char *str, t_env *fake_env)
{ 
    char *next_str;
    //printf("i'm in the fiunction\n");
    //printf("str is %s\n", str);
    while (*str == '$')//******* do i have to verify here echo jhfgjh$USER
        str++;
    if(*str)
    {
        if (*(str) == '?')
        {
            //printf("*str++ is %c\n", *str);
            char *status = ft_itoa(exit_status);
            /* printf("int g_status = %d\n", g_status);
            printf("str g_status = %s\n", g); */
            ft_putstr_fd(status, STDIN_FILENO);
            str++;
        }
        if (i == 0 && *str != '$')
        {
            i = 1;
            next_str = get_next_str(str, '$');
            //printf("\nstr %s and next_str %s\n print str ",str,  next_str);
            ft_putstr(str);
            //printf("\n");
        }
        else
        //printf("str is %s\n", str);
            next_str = get_next_str(str, '$');//or it finds $ or it does not find it
        // printf("next_str %s\n", next_str);
        // printf("str after next_str is %s\n", str);

        // printf("fake_env %p\n", fake_env->var_name);
        char *value = find_env_value(str, fake_env);
        //printf("my str is env_variable or not %s\n", value);
        if (value)
            ft_putstr(value);
        // else
        //      ft_putstr(str);
        if (next_str)
            ft_dollar(1 ,next_str, fake_env);
    } 
    else
        ft_putstr("$");
}
