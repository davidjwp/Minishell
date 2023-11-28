#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct HERDstruct{
	char				*input;
	struct HERDstruct	*next;
}	t_herdst;

enum	e_type{
	WORD,
	SEPR,
	HERD,
	EXST,
	APRD,
	SQUO,
	ARGT,
	OPER,
	REDL,
	VARE,
	DQUO,
	BUIT,
	REDR,
	COMD,
	PIPE,
};

typedef struct testToken{
	char	*content;
	int		type;
	int		len;
}	t_token;

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*duplicate;
	int		index;

	index = 0;
	duplicate = malloc(ft_strlen((char *)s) + 1);
	if (!duplicate)
		return (0);
	while (s[index])
	{
		duplicate[index] = s[index];
		index++;
	}
	duplicate[index] = '\0';
	return (duplicate);
}

int	check_input(char *input, char *exit)
{
	if (input == NULL)
		return (1);
	if (!*input)
		return (1);
	for (int i = 0; input[i] != 0; i++)
		if (input[i] != exit[i])
			return (1);
	return (0);
}

int	init_herdst(t_herdst *_hdherd)
{
	_hdherd = malloc(sizeof(t_herdst));
	if (_hdherd == NULL)
		return (0);
	_hdherd->input = NULL;
	_hdherd->next = NULL;
	return (1);
}

int	add_input(t_herdst *_hdherd, char *input)
{
	t_herdst	*tmp;
	t_herdst	*new;

	tmp = _hdherd;
	if (input == NULL)
		return (1);
	while (tmp->next != NULL)
		tmp = tmp->next;
	if (!init_herdst(new))
		return (0);
	new->input = ft_strdup(input);
	return (1);
}


// int	main(int argc, char **argv)
// {
// 	char		*input;
// 	t_token		**tokens;
// 	t_herdst	*_hdherd;
// 	char		*herdoc;

// 	input = NULL;
// 	if (!init_herdst(_hdherd))
// 		return (printf("malloc init_herdst fail\n"), 0);
// 	if (argc != 2)
// 		return (1);
// 	while (check_input(input, argv[1]))
// 	{
// 		if (!add_input(_hdherd, input))
// 			return (2);
// 		if (input != NULL)
// 			free(input);
// 		input = readline("> ");
// 	}
// 	if (!add_input(_hdherd, input))
// 		return (3);
// 	free(input);
// 	if (!comp_herdstr(_hdherd))
// 		return (4);
// 	add_history(herdoc);
// 	return (5);
// }

int	main(void)
{
	char	*input;
	int		i;

	i = 0;
	while (i++ < 2)
	{
		input = readline("> ");
		add_history(input);
		add_history("hello\nthis\nis\na\nlong\nline\n");
	}
	return (1);
}