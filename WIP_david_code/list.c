# include <stdio.h>

enum	e_type{
	PIPE,
	COMD,
	REDI
};

typedef struct s_token
{
	char	*content;
	int 	len;
	int		type;
}			t_token;


typedef struct  s_node{
	struct s_node	*parent;
	struct s_token	**token;
	int				type;
	struct s_node	*right;
	struct s_node	*left;
}				t_node;

int	main(void)
{
	const char	input[] = "cat file.txt | grep \"keyword\" | sort";
	t_node	*node1;
	t_node	*node2;
	t_node	*node3;
	t_node	*node4;
	t_node	*node5;

//node1
	node1->left = node2;
	node1->right = node3;
	node1->parent = NULL;
	node1->type = PIPE;

//node2
	node2->left = NULL;
	node2->right = NULL;
	node2->parent = node1;
	node2->token[0]->content = "cat";
	node2->token[1]->content = "file.txt";
	node2->type = COMD;

//node3
	node3->left = node4;
	node3->right = node5;
	node3->parent = node1;
	node3->type = PIPE;
//node4
	node4->left = NULL;
	node4->right = NULL;
	node4->parent = node3;
	node4->token[0]->content = "grep";
	node4->token[1]->content = "\"keyword\"";
	node4->type = COMD;

//node5
	node5->left = NULL;
	node5->right = NULL;
	node5->parent = node3;
	node5->token[0]->content = "sort";
	node5->type = COMD;
}