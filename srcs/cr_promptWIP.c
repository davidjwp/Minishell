#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define DFLT_PROMPT "$> "
#define BUF_SIZ 1024
#define GREEN "\033[1m\033[32m"
#define BLUE "\033[1m\033[34m"
#define RESET "\033[0m"

/*
	THIS IS FOR CREATING A BASH ACCURATE PROMPT, IT IS NOT FINISHED
	MISSING THE ADDED COLOURS AND I"M NOT SURE ABOUT THE
	CURRENT WORKING DIRECTORY
*/

typedef struct LittleStorage{
	int	x;
	int	y;
	int	z;
}	t_lstorage;

bool	cmp_paths(char *buf, char *path)
{
	int	i;

	i = 0;
	while (buf[i] == path[i] && path[i])
		i++;
	if (!path[i] && buf[i])
		return (true);
	return (false);
}

char	*trim_cwd(char *buf, char **split)
{
	char	*cwd;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (!cmp_paths(buf, split[i]) && split[i] != NULL)
		i++;
	if (split[i] == NULL)
	{
		len = ft_strlen(buf);
		i = 0;
	}
	else
	{
		len = ft_strlen(buf) - ft_strlen(split[i]);
		i = ft_strlen(split[i]);
	}
	cwd = malloc(sizeof(char) * (len + 1));
	if (!cwd)
		return (NULL);
	cwd = ft_strncpy(cwd, &buf[i]);
	return (cwd);
}

/*
*	this function will first check if there are any envs, if not 
*	i use the default prompt, then i create a cut current working directory
*	by checking if the cwd has any of the PATH env in it, if so i cut it out
*	else it stays the same, then i create the prompt using all the other PATH
*	envs and the cwd. 
*	this creates a prompt that should act like the bash prompt while still 
*	having a prompt if no environment is given
*/

//USER@NAME:~cwd this is the way the prompt would be structured 
char	*crt_prompt(char *user, char *name, char *cwd)
{
	t_lstorage	prst;
	char		*prompt;
	char		cut_cwd;

	if (!user || !name || !cwd)
		return (DFLT_PROMPT);
	cut_cwd = trim_cwd(cwd, ft_split(getenv("PATH"), ':'));
	if (!cut_cwd)
		return (err_msg("trim_cwd malloc fail"), NULL);
	prst = (t_lstorage){ft_strlen(user), ft_strlen(name), ft_strlen(cut_cwd)};
	prompt = ft_calloc((prst.x + prst.y + prst.z + 6), sizeof(char));
	ft_strcat(prompt, user, prst.x);
	prompt[ft_strlen(prompt)] = '@';
	ft_strcat(&prompt[prst.x + 1], name, prst.y);
	prompt[ft_strlen(prompt)] = ':';
	prompt[ft_strlen(prompt)] = '~';
	ft_strcat(&prompt[prst.x + prst.y + 2], cut_cwd, prst.z);
	prompt[ft_strlen(prompt)] = '$';
	prompt[ft_strlen(prompt)] = ' ';
	return (prompt);
}
