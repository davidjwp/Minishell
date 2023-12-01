#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define STR "abcd"
#define OSTR "hello"

int	ft_strlen(char *str)
{
	int	len;

	while (str[len])
		len++;
	return (len);
}

void	ft_strcpy(char *ptr1, char *str)
{
	int	i = 0;

	while (str[i])
	{
		ptr1[i] = str[i];
		i++;
	}
	ptr1[i] = 0;
}

int	main(void)
{
	char *ptr1;
	char *ptr2;

	ptr1 = malloc(sizeof(char) * (ft_strlen(STR) + 1));
	ft_strcpy(ptr1, STR);
	ptr2 = ptr1;
	ptr1 = malloc(sizeof(char) * (ft_strlen(OSTR) + 1));
	ft_strcpy(ptr1, OSTR);
	free(ptr1);
	free(ptr2);
	return (0);
}