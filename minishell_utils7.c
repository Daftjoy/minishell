/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:56:53 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/03 17:25:12 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(void)
{
	write(1, "Error: ", 7);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
}

void	ft_move_pos(t_args *mini, int i)
{
	int j;

	j = i;
	while (mini->type[i] == ',' || mini->type[i] == '>')
		i++;
	mini->type = mini->type + i;
}

void	ft_only_redir(t_args *mini, char **env)
{
	int pid;
	int fd_file;

	fd_file = ft_open_file(mini, 0);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_file, 1);
		ft_exe(mini->commands[0], mini->commands, env);
	}
	else
		wait(NULL);
	if (mini->type[mini->arg] == '|')
	{
		mini->arg++;
		ft_redir(mini, env);
	}
}

void	ft_echo_pwd(char **argu)
{
	if (!ft_strcmp("echo", argu[0]))
		ft_echo(argu);
	else if (!ft_strcmp("pwd", argu[0]))
		ft_pwd(0);
	exit(0);
}
