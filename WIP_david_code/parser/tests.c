#include <fcntl.h>
#include "../Minishell.h"

/*TESTS|________________________*/

/*
	WORD,
	SEPR,
	QUOT,
	EXST, don't use that
	APRD,
	HERD,
	ARGT, might not need that, i don't use it for now
	OPER, don't need that since the only operators are redirections
	REDL,
	VARE, using this but only in quotes, outside of quotes for global variables  
	PIPE,
	BUIT,
	REDR,
	COMD,
	ECHO = 22,
	CD = 33,
	PWD = 44,
	EXPORT = 55,
	UNSET = 66,
	ENV = 77,
	EXIT = 88

*/

char	*get_type(int type)
{
	if (type > 13){
		switch (type){
			
			case 22:
				return ("ECHO");
			case 33:
				return ("CD");
			case 44:
				return ("PWD");
			case 55:
				return ("EXPORT");
			case 66:
				return ("UNSET");
			case 77:
				return ("ENV");
			case 88:
				return ("EXIT");
		}
	}
	return ((char *[14]){"WORD", "SEPARATOR", "QUOTE", "EXIT_STATUS", \
	"APPEND_REDIRECTION", "HERE_DOC", "ARGUMENT", "OPERATOR", \
	"LEFT_REDIRECTION", "VARIABLE", "PIPELINE", "BUILT_IN", \
	"RIGHT_REDIRECTION", "COMMAND"}[type]);
}

void	print_node(t_astn *node, FILE *file)
{
	fprintf (file, "\t_______________\n");
	fprintf (file, "node\t- %p\n", node);
	fprintf (file, "type\t- %s\n", get_type(node->type));
	fprintf (file, "parent\t- %p\n", node->parent);
	fprintf (file, "right\t- %p\n", node->right);
	fprintf (file, "left\t- %p\n", node->left);
	if (node->token != NULL){
		fprintf (file, "\"");
		for (int i = 0; node->token[i] != NULL; i++)
			fprintf (file, "%s ", node->token[i]->content);
		fprintf(file, "\"\n");
		for (int i = 0; node->token[i] != NULL; i++)
			fprintf (file, "%s ", get_type(node->token[i]->type));
	}
	fprintf (file, "\n\n");
}

void	print_tree(t_astn *node, FILE *file)
{
	print_node(node, file);
	if (node->left != NULL)
		print_tree(node->left, file);
	if (node->right != NULL)
		print_tree(node->right, file);
}

int	main(int argc, char **argv)
{
	t_astn		*tree;
	size_t		index = 0;
	// const char	input[] = "cat << EOF > file | wc -c | tr -d "" > file2";
	// const char	input[] = "echo hello > file | cat > file2";
	int	error = 0;
	FILE *file = fopen("file", "wa+");

	if (argc != 2)
		return (printf ("Error missing input\n"), 0);
	tree = create_ast(argv[1], &index, &error, NULL);
	fprintf(file, "%s\n\n", argv[1]);
	print_tree(tree, file);
	free_tree(tree);
	return (1);
}