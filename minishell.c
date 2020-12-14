/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:30:49 by antmarti          #+#    #+#             */
/*   Updated: 2020/12/14 19:13:03 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_subpro(t_args *mini, char **env)
{
	int	**fd;
	int	pid;
	int	i;

	i = 0;
	fd = malloc(ft_strlen(mini->type) * sizeof(int *));
	while (i < (int)ft_strlen(mini->type))
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	pipe(fd[0]);
	mini->commands = ft_split(mini->args2[0], ' ');
	pid = fork();
	if (pid == 0)
	{
		close(fd[0][0]);
		dup2(fd[0][1], 1);
		close(fd[0][1]);
		ft_exe(mini->commands[0], mini->commands, env);
	}
	else
	{
		i = 1;
		while (i < (int)ft_strlen(mini->type))
		{
			mini->commands = ft_split(mini->args2[i], ' ');
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
		}
		mini->commands = ft_split(mini->args2[i], ' ');
		close(fd[i - 1][1]);
		if (ft_strlen(mini->type) > 1)
			close(fd[i - 2][0]);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[i - 1][0], 0);
			close(fd[i - 1][0]);
			ft_exe(mini->commands[0], mini->commands, env);
		}
	}
	close(fd[0][0]);
	i = -1;
	while (++i <= (int)ft_strlen(mini->type))
		wait(NULL);
	mini->type[0] = '\0';
	i = -1;
	while (++i < (int)ft_strlen(mini->type))
		free(fd[i]);
	free(fd);
}

void		ft_read_command(char **env, t_args *mini)
{
	int		i;
	pid_t	childpid;

	i = -1;
	while (mini->args[++i])
	{
		//dup2(mini->in, 0);
		//dup2(mini->out, 1);
		mini->args2 = ft_split2(mini->args[i], mini);
		if (mini->type[0] == 0)
		{
			mini->commands = ft_split(mini->args2[0], ' ');
			childpid = fork();
			if (childpid >= 0)
			{
				if (childpid != 0)
					wait(NULL);
				else
					ft_exe(mini->commands[0], mini->commands, env);
			}
		}
		else
			ft_subpro(mini, env);
	}
}

void		ft_loop(char **env)
{
	t_args	*mini;

	mini = malloc(sizeof(t_args));
	mini->main_chain = 0;
	mini->args = 0;
	//mini->in = dup(0);
	//mini->out = dup(1);
	write(1, "... ", 4);
	while (get_next_line(0, &mini->main_chain))
	{
		mini->args = ft_split(mini->main_chain, ';');
		ft_read_command(env, mini);
		write(1, "... ", 4);
		free(mini->main_chain);
	}
}

int			main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_loop(env);
	return (0);
}
