/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:56:53 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/02 19:57:45 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
