#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUF_SIZ 1024
#define	GREEN "\033[1m\033[32m"
#define RESET "\033[0m"
#define BLUE "\033[1m\033[34m"

int		ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, char *srce)
{
	int	i;

	i = 0;
	while (srce[i])
	{
		dest[i] = srce[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*trim(char *buf)
{
	char 	*cwd;
	int		len;
	int		i;

	len = 0;
	i = ft_strlen(buf);
	while (buf[--i] != '/' && i >= 0)
		len++;
	cwd = malloc(sizeof(char) * (len + 2));
	cwd = ft_strncpy(cwd, &buf[i]);
	return (cwd);
}

int	main(int argc, char **argv, char **env)
{
	char	buf[BUF_SIZ];
	char	*cwd;

	getcwd(buf, BUF_SIZ);
	cwd = trim(buf);
	printf ("%s%s@%s%s:%s~%s%s$ \n", GREEN, getenv("USER"), getenv("NAME"), RESET, BLUE, cwd, RESET);
	free(cwd);
	return (0);
}
