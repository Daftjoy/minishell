/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:25:13 by agianico          #+#    #+#             */
/*   Updated: 2021/03/09 20:19:51 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir(t_args *mini, char **env)
{
	int pid;

	mini->commands = ft_split(mini->args2[mini->arg], ' ');
	if (mini->type[mini->arg] == ',' || mini->type[mini->arg] == '>')
		ft_only_redir(mini, env);
	else if (mini->type[mini->arg] == '<')
		ft_input(mini, env);
	else if (!(mini->type[mini->arg]))
	{
		pid = fork();
		if (pid == 0)
			ft_exe(mini->commands[0], mini->commands, env, mini);
		else
			waitpid(pid, &mini->exit_status, 0);
		return ;
	}
	else
		ft_pipe(mini, env);
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
		ft_exe(mini->commands[0], mini->commands, env, mini);
	}
	else
		waitpid(pid, &mini->exit_status, 0);
	if (mini->type[mini->arg] == '|')
	{
		mini->arg++;
		ft_redir(mini, env);
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
