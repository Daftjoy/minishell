/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:11:35 by agianico          #+#    #+#             */
/*   Updated: 2021/03/11 17:57:18 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pipe(t_args *mini, char **env)
{
	int		**fd;
	pid_t	pid;
	int		pipe_numb;

	fd = ft_fd_creater(mini, &pipe_numb);
	pid = fork();
	if (pid == 0)
		fd = ft_firstdup(fd, env, mini);
	else
	{
		waitpid(pid, &g_status, 0);
		if (g_status != 0)
		{
			pid = fork();
			if (pid == 0)
				exit(ft_arg_error(mini, 1));
			else
				wait(NULL);
		}
		else
			fd = ft_final_dup(fd, env, mini);
	}
	return (ft_wait(fd, env, mini, pipe_numb));
}

int		**ft_fd_creater(t_args *mini, int *j)
{
	int pipe_numb;
	int **fd;
	int i;

	pipe_numb = 0;
	i = 0;
	while (mini->type[pipe_numb + mini->arg] == '|')
		pipe_numb++;
	fd = malloc(pipe_numb * sizeof(int *));
	while (i < pipe_numb)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	pipe(fd[0]);
	*j = pipe_numb;
	return (fd);
}

int		**ft_firstdup(int **fd, char **env, t_args *mini)
{
	close(fd[0][0]);
	dup2(fd[0][1], 1);
	close(fd[0][1]);
	ft_exe(mini->commands[0], mini->commands, env, mini);
	return (fd);
}

int		**ft_mid_dup(int **fd, char **env, t_args *mini, int *j)
{
	pid_t	pid;
	int		i;
	char	*trim;

	i = 1;
	mini->arg++;
	while (mini->type[mini->arg] == '|' && g_status == 0)
	{
		ft_free_arr(mini->commands);
		trim = ft_mini_trim(mini->args2[mini->arg]);
		mini->commands = ft_split(trim, ' ');
		free (trim);
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
			ft_exe(mini->commands[0], mini->commands, env, mini);
		}
		else
		{
			waitpid(pid, &g_status, 0);
			if (g_status != 0)
			{
				pid = fork();
				if (pid == 0)
					exit(ft_arg_error(mini, 1));
				else
					wait(NULL);
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
	pid_t	pid;
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
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[i - 1][0], 0);
		close(fd[i - 1][0]);
		if (fd_file)
			dup2(fd_file, 1);
		ft_exe(mini->commands[0], mini->commands, env, mini);
	}
	else
		waitpid(pid, &g_status, 0);
	ft_free_arr(mini->commands);
	return (fd);
}
