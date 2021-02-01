/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:30:49 by antmarti          #+#    #+#             */
/*   Updated: 2021/02/01 19:59:40 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_input(t_args *mini, char **env)
{
	int fd_file;
	int i;
	int pid;

	i = 0;
	while (mini->type[i] == '<')
	{
		fd_file = open(ft_strtrim(mini->args2[i + mini->arg + 1], " "),
		O_RDONLY, S_IRWXU);
		i++;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_file, 0);
		if (mini->type[i] == '>' || mini->type[i] == ',')
			dup2(ft_open_file(mini, i), 1);
		ft_exe(mini->commands[0], mini->commands, env);
	}
	else
		wait(NULL);
	mini->type = mini->type + i;
	mini->arg = mini->arg + i + 1;
	if (ft_strchr(mini->type, '|'))
	{
		if (mini->type[0] == '>' || mini->type[0] == ',')
		{
			i = 0;
			while (mini->type[i] == '>' || mini->type[i] == ',')
			{
				mini->arg++;
				mini->type = mini->type + 1;
				i++;
			}
			mini->type = mini->type + 1;
			ft_redir(mini, env);
		}
	}
}

int			ft_open_file(t_args *mini, int i)
{
	int fd_file;

	while (mini->type[i] == ',' || mini->type[i] == '>')
	{
		if (mini->type[i] == ',')
			fd_file = open(ft_strtrim(mini->args2[i + mini->arg  + 1], " "), O_CREAT
			| O_WRONLY | O_APPEND, S_IRWXU);
		else
			fd_file = open(ft_strtrim(mini->args2[i + mini->arg + 1], " "), O_CREAT
			| O_WRONLY | O_TRUNC, S_IRWXU);
		i++;
	}
	mini->type = mini->type + i;
	mini->arg = mini->arg + i + 1;
	return (fd_file);
}

void		ft_only_redir(t_args *mini, char **env)
{
	int fd_file;
	int pid;

	fd_file = ft_open_file(mini, 0);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_file, 1);
		ft_exe(mini->commands[0], mini->commands, env);
	}
	else
		wait(NULL);
	if (ft_strchr(mini->type, '|'))
	{
		mini->type = mini->type + 1;
		ft_redir(mini, env);
	}
}

void		ft_redir(t_args *mini, char **env)
{
	int pid;

	mini->commands = ft_split(mini->args2[mini->arg], ' ');
	if (mini->type[0] == ',' || mini->type[0] == '>')
		ft_only_redir(mini, env);
	else if (mini->type[0] == '<')
	{
		ft_input(mini, env);
	}
	else if (!ft_strchr(mini->type, '|'))
	{
		pid = fork();
		if (pid == 0)
			ft_exe(mini->commands[0], mini->commands, env);
		else
			wait(NULL);
		return ;
	}
	else
		ft_subpro(mini, env);
}

int			ft_subpro(t_args *mini, char **env)
{
	int	**fd;
	int	pid;
	int	i;

	i = 0;
	fd = malloc(ft_strlen(mini->type) * sizeof(int *));
	while (mini->type[i] == '|')
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	pipe(fd[0]);
	mini->commands = ft_split(mini->args2[mini->arg], ' ');
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
		while (mini->type[i] == '|')
		{
			mini->commands = ft_split(mini->args2[mini->arg + i], ' ');
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
		mini->commands = ft_split(mini->args2[mini->arg + i], ' ');
		close(fd[i - 1][1]);
		if (i > 1)
			close(fd[i - 2][0]);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[i - 1][0], 0);
			close(fd[i - 1][0]);
			if (mini->type[i] == '>')
				dup2(ft_open_file(mini, i), 1);
			ft_exe(mini->commands[0], mini->commands, env);
		}
	}
	close(fd[0][0]);
	i = 0;
	wait(NULL);
	while (mini->type[i] == '|')
	{
		wait(NULL);
		i++;
	}
	while (mini->type[i] == '|')
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	mini->type = mini->type + i + 1;
	mini->arg = mini->arg + i + 1;
	if (ft_strchr(mini->type, '|'))
	{
		mini->type = mini->type + 1;
		mini->arg = mini->arg + 1;
		ft_redir(mini, env);
	}
	return (i);
}

void		ft_read_command(char **env, t_args *mini)
{
	int		i;
	pid_t	childpid;

	i = -1;
	while (mini->args[++i])
	{
		mini->args2 = ft_split2(mini->args[i], mini);
		mini->arg = 0;
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
			ft_redir(mini, env);
	}
}

void		ft_loop(char **env)
{
	t_args	*mini;

	mini = malloc(sizeof(t_args));
	mini->main_chain = 0;
	mini->args = 0;
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
