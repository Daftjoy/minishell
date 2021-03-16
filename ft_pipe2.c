/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 12:12:48 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/16 14:13:24 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free(trim);
	close(fd[i - 1][1]);
	if (i > 1)
		close(fd[i - 2][0]);
	env = ft_final_dup2(env, mini, i, fd);
	return (fd);
}

char	**ft_final_dup2(char **env, t_args *mini, int i, int **fd)
{
	int fd_file;

	fd_file = 0;
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
		return (env);
	}
	else
		ft_final_dup3(mini);
	return (env);
}

void	ft_final_dup3(t_args *mini)
{
	waitpid(g_pid, &g_status, 0);
	if (g_status != 0)
	{
		g_pid = fork();
		if (g_pid == 0)
			exit(ft_pipe_error(mini));
		else
			waitpid(g_pid, &g_status, 0);
	}
}
