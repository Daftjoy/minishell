#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	pid_t childPID;
	//(void)env;
	int i;
	char **paths;
	char *p;
	int	j;
	char *s;
	char *st;

	i = 0;
	j = 1;
	st = "hola";
	while (env[i])
	{
		if (!ft_strcmp("PATH", ft_substr(env[i], 0, 4)))
			paths = ft_split(env[i], ':');
		i++;
	}

	while (get_next_line(0, &s))
	{
		childPID = fork();
		if (childPID >= 0)
		{
			if (childPID != 0)
			{
				wait(NULL);
			}
			else
			{
				i = 0;
				while (paths[i])
				{
					//get_next_line(0, &s);
					p = malloc(100);
					p = ft_strjoin(paths[i], "/");
					p = ft_strjoin(p, (const char*)s);
					execve(p, argv, env);
					i++;
					p = 0;
					free(p);
				}
			}
		}
		free(s);
	}
	return (0);
}
