#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	//(void)env;
	int i;
	char **paths;
	char *p;
	int j;

	i = 0;
	p = malloc(100);
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A')
			paths = ft_split(env[i], ':');
		i++;
	}
	i = 0;
	while (paths[i])
	{
		/*
		Ya nos guarda cada posibe path ahora hay que copiarla añadiéndole el nombre del comando
		y probar a ejecutar con execve
		 */
		j = 0;
		while (paths[i][j])
		{
			p[j] = paths[i][j];
			j++;
		}
		p [j] = '/';
		p [j + 1] = 'l';
		p [j + 2] = 's';
		p [j + 3] = '\0';
		execve(p, argv, env);
		i++;
	}
	return (0);
}
