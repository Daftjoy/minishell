/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:11:35 by agianico          #+#    #+#             */
/*   Updated: 2021/03/15 20:48:07 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pipe(t_args *mini, char **env)
{
	int		**fd;
	int		i;

	fd = ft_fd_creater(mini, &mini->pipe_num);
	g_pid = fork();
	if (g_pid == 0)
		fd = ft_firstdup(fd, env, mini);
	else
	{
		waitpid(g_pid, &g_status, 0);
		if (g_status != 0)
		{
			g_pid = fork();
			if (g_pid == 0)
				exit(ft_pipe_error(mini));
			i = 0;
			while (i < mini->pipe_num)
			{
				free(fd[i]);
				i++;
			}
			free(fd);
			fd = ft_fd_creater(mini, &mini->pipe_num);
		}
		fd = ft_final_dup(fd, env, mini);
	}
	return (ft_wait(fd, env, mini, mini->pipe_num));
}

int		**ft_fd_creater(t_args *mini, int *j)
{
	int **fd;
	int i;

	mini->pipe_num = 0;
	i = 0;
	while (mini->type[mini->pipe_num + mini->arg] == '|')
		mini->pipe_num++;
	fd = malloc(mini->pipe_num * sizeof(int *));
	while (i < mini->pipe_num)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	pipe(fd[0]);
	*j = mini->pipe_num;
	return (fd);
}

int		**ft_firstdup(int **fd, char **env, t_args *mini)
{
	close(fd[0][0]);
	dup2(fd[0][1], 1);
	close(fd[0][1]);
	env = ft_functs(env, mini);
	return (fd);
}

int		**ft_mid_dup(int **fd, char **env, t_args *mini, int *j)
{
	int		i;
	char	*trim;
	int		k;

	i = 1;
	k = 0;
	mini->arg++;
	while (mini->type[mini->arg] == '|')
	{
		ft_free_arr(mini->commands);
		trim = ft_mini_trim(mini->args2[mini->arg]);
		mini->commands = ft_split(trim, ' ');
		free (trim);
		close(fd[i - 1][1]);
		pipe(fd[i]);
		g_pid = fork();
		if (g_pid == 0)
		{
			close(fd[i][0]);
			dup2(fd[i - 1][0], 0);
			close(fd[i - 1][0]);
			dup2(fd[i][1], 1);
			close(fd[i][1]);
			env = ft_functs(env, mini);
		}
		else
		{
			waitpid(g_pid, &g_status, 0);
			if (g_status != 0)
			{
				g_pid = fork();
				if (g_pid == 0)
					exit(ft_pipe_error(mini));
			}
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
	char	*trim;

	i = 0;
	fd_file = 0;
	fd = ft_mid_dup(fd, env, mini, &i);
	ft_free_arr(mini->commands);
	trim = ft_mini_trim(mini->args2[mini->arg]);
	mini->commands = ft_split(trim, ' ');
	free (trim);
	close(fd[i - 1][1]);
	if (i > 1)
		close(fd[i - 2][0]);
	if (mini->type[mini->arg] == '>' || mini->type[mini->arg] == ',')
		fd_file = ft_open_file(mini, i);
	g_pid = fork();
	if (g_pid == 0)
	{
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
		if (fd_file)
			dup2(fd_file, 1);
		env = ft_functs(env, mini);
	}
	else
		waitpid(g_pid, &g_status, 0);
	return (fd);
}
