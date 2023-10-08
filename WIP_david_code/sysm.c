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

int	main(void)
{
	t_str *node;

	node = malloc(sizeof(t_str));
	node->l = malloc(sizeof(t_po) * 3);
	node->l[0] = malloc(sizeof(t_po));
	node->l[0]->c = 0;
	free(node);
	free(node->l);
	free(node->[0]);
	return 0;
}
