#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	env[] = "PATH";

	printf ("%s\n", getenv(env) ? getenv(env) : "env not found");
	return (0);
}