# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_po{
	int	t;
	char c;
}			t_po;

typedef struct s_str{
	void			*ptr;
	t_po			**l;
	struct s_str	*ssl;
}		t_str;

void	funct(const char *str)
{
	size_t	i = 0;

	while (str[i] != 0)
		i++;
}

int	main(void)
{
	const char	str[] = "heeeyyeyeye";

	funct(&str[5]);
	return (0);
}
