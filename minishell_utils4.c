/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:18:26 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/02 19:58:03 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_squotes(char *argu)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
	k = 0;
	str = malloc(ft_count(argu, 1));
	while (argu[i])
	{
		if (argu[i] != '\'')
		{
			str[k] = argu[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	return (str);
}

int		**ft_firstdup(int **fd, char **env, t_args *mini)
{
	close(fd[0][0]);
	dup2(fd[0][1], 1);
	close(fd[0][1]);
	ft_exe(mini->commands[0], mini->commands, env);
	return (fd);
}

int		**ft_mid_dup(int **fd, char **env, t_args *mini, int *j)
{
	pid_t	pid;
	int		i;

	i = 1;
	mini->arg++;
	while (mini->type[mini->arg] == '|')
	{
		mini->commands = ft_split(mini->args2[mini->arg], ' ');
		close(fd[i - 1][1]);
		pipe(fd[i]);
		pid = fork();
		if (pid == 0)
		{
			close(fd[i][0]);
			dup2(fd[i - 1][0], 0);
			close(fd[i - 1][0]);
			dup2(fd[i][1], 1);
			close(fd[i][1]);
			ft_exe(mini->commands[0], mini->commands, env);
		}
		i++;
		mini->arg++;
	}
	*j = i;
	return (fd);
}

int		**ft_final_dup(int **fd, char **env, t_args *mini)
{
	int		i;
	int		fd_file;
	pid_t	pid;

	i = 0;
	fd = ft_mid_dup(fd, env, mini, &i);
	mini->commands = ft_split(mini->args2[mini->arg], ' ');
	close(fd[i - 1][1]);
	if (i > 1)
		close(fd[i - 2][0]);
	if (mini->type[mini->arg] == '>')
		fd_file = ft_open_file(mini, i);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
		if (mini->type[mini->arg] == '>')
			dup2(fd_file, 1);
		ft_exe(mini->commands[0], mini->commands, env);
	}
	else
		wait(NULL);
	return (fd);
}

int		ft_wait(int **fd, char **env, t_args *mini, int pipe_numb)
{
	int i;

	i = 0;
	while (i < pipe_numb)
	{
		wait(NULL);
		free(fd[i]);
		i++;
	}
	free(fd);
	if (mini->type[mini->arg] && mini->type[mini->arg] == '|')
	{
		mini->arg++;
		ft_redir(mini, env);
	}
	return (i);
}
