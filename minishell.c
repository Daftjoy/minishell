/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:23:38 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/02 19:59:34 by antmarti         ###   ########.fr       */
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
			ft_exe(mini->commands[0], mini->commands, env);
		else
			wait(NULL);
		return ;
	}
	else
		ft_pipe(mini, env);
}

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
		fd = ft_final_dup(fd, env, mini);
	close(fd[0][0]);
	return (ft_wait(fd, env, mini, pipe_numb));
}

void	ft_read_command(char **env, t_args *mini)
{
	int		i;

	i = -1;
	while (mini->args[++i])
	{
		mini->args2 = ft_split2(mini->args[i], mini);
		mini->arg = 0;
		if (mini->type[0] == 0)
		{
			mini->commands = ft_split(mini->args2[0], ' ');
			env = ft_functs(env, mini);
		}
		else
			ft_redir(mini, env);
	}
}

void	ft_loop(char **env)
{
	t_args	*mini;
	int		i;
	char	**env2;

	mini = malloc(sizeof(t_args));
	mini->main_chain = 0;
	mini->args = 0;
	write(1, "... ", 4);
	i = 0;
	while (env[i])
		i++;
	env2 = malloc(sizeof(char *) * i);
	i = -1;
	while (env[++i])
		env2[i] = ft_strdup(env[i]);
	env2[i] = 0;
	while (get_next_line(0, &mini->main_chain))
	{
		mini->args = ft_split(mini->main_chain, ';');
		ft_read_command(env2, mini);
		write(1, "... ", 4);
		free(mini->main_chain);
	}
	free(env2);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_loop(env);
	return (0);
}
