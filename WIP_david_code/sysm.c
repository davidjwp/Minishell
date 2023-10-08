# include <stdio.h>
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

void	funct(size_t *p)
{
	for (int i = 0; i < 2; i++)
		*p += 1;
	return ;
}

int	main(void)
{
	t_str *node;

	funct(0);
	return (0);
}
