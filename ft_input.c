/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:26:36 by agianico          #+#    #+#             */
/*   Updated: 2021/03/15 21:47:15 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(t_args *mini, char **env)
{
	int		fd_file;
	char	*trim;

	while (mini->type[mini->arg] == '<')
	{
		trim = ft_strtrim(mini->args2[mini->arg + 1], " ");
		fd_file = open(trim, O_RDONLY, S_IRWXU);
		if (fd_file < 0)
		{
			ft_error();
			return ;
		}
		mini->arg++;
	}
	if (mini->type[mini->arg] == '|')
		ft_input_pipe(env, mini, fd_file);
	else
		ft_input_2(env, mini, fd_file);
}

void	ft_input_pipe(char **env, t_args *mini, int fd_file)
{
	int		pipe_numb;
	int		**fd;

	pipe_numb = 0;
	fd = ft_fd_creater(mini, &pipe_numb);
	g_pid = fork();
	if (g_pid == 0)
	{
		ft_d(fd_file);
		fd = ft_firstdup(fd, env, mini);
	}
	else
		fd = ft_final_dup(fd, env, mini);
	ft_wait(fd, env, mini, pipe_numb);
}

void	ft_input_2(char **env, t_args *mini, int fd_file)
{
	g_pid = fork();
	if (g_pid == 0)
	{
		ft_d(fd_file);
		if (mini->type[mini->arg] == '>' || mini->type[mini->arg] == ',')
			dup2(ft_open_file(mini, mini->arg), 1);
		ft_exe(mini->commands[0], mini->commands, env, mini);
	}
	else
		waitpid(g_pid, &g_status, 0);
}

void	ft_d(int fd_file)
{
	dup2(fd_file, 0);
	close(fd_file);
}
