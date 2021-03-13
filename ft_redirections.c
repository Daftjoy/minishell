/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:25:13 by agianico          #+#    #+#             */
/*   Updated: 2021/03/11 17:57:27 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_trim_counter(char *str)
{
	int i;
	int j;
	int opt;
	int k;

	i = 0;
	j = 0;
	k = 0;
	opt = 0;
	while (str[i])
	{
		if (str[i] != ' ' && !opt && str[i] > 0)
			opt = 1;
		if (opt)
			j++;
		i++;
	}
	return (j);
}

char	*ft_mini_trim(char *str)
{
	int		i;
	int		j;
	int		k;
	int		opt;
	char	*ret;

	j = ft_trim_counter(str);
	ret = malloc(j + 1);
	i = 0;
	k = 0;
	opt = 0;
	while (str[i])
	{
		if (str[i] != ' ' && !opt && str[i] > 0)
			opt = 1;
		if (opt)
		{
			ret[k] = str[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	return (ret);
}

char	**ft_redir(t_args *mini, char **env)
{
	char *trim;

	trim = ft_mini_trim(mini->args2[mini->arg]);
	mini->commands = ft_split(trim, ' ');
	free(trim);
	if (mini->type[mini->arg] == ',' || mini->type[mini->arg] == '>')
		ft_only_redir(mini, env);
	else if (mini->type[mini->arg] == '<')
		ft_input(mini, env);
	else if (!(mini->type[mini->arg]))
		env = ft_functs(env, mini);
	else
		ft_pipe(mini, env);
	return (env);
}

void	ft_only_redir(t_args *mini, char **env)
{
	int	pid;
	int	fd_file;

	fd_file = ft_open_file(mini, 0);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_file, 1);
		env = ft_functs(env, mini);
	}
	else
	{
		waitpid(pid, &g_status, 0);
		if (g_status != 0)
			ft_pipe_error(mini);
	}
	if (mini->type[mini->arg] == '|')
	{
		mini->arg++;
		env = ft_redir(mini, env);
	}
}

int		ft_open_file(t_args *mini, int i)
{
	int		fd_file;
	char	*str;

	i = 0;
	while (mini->type[mini->arg] == ',' || mini->type[mini->arg] == '>')
	{
		str = ft_strtrim(mini->args2[mini->arg + 1], " ");
		if (mini->type[mini->arg] == ',')
			fd_file = open(str, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		else
			fd_file = open(str, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		mini->arg++;
		free(str);
	}
	return (fd_file);
}
