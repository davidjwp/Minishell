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


int	main(void)
{
	const char	str[] = "this is a string of words";
	char		his[256] = {0};
	int	len = strlen(str);

	for (int i = 0; i < len; i++)
		his[str[i]]++;
	return (0);
}
