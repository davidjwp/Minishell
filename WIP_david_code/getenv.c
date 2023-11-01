# include <stdlib.h>
# include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	char	*l_env;
	
	l_env = getenv(env[2]);

	printf ("%s\n", l_env);
	return (0);
}