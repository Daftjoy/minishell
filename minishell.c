/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:30:49 by antmarti          #+#    #+#             */
/*   Updated: 2021/02/12 19:52:06 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_input(t_args *mini, char **env)
{
	int fd_file;
	int i;
	int pid;
	int **fd;

	i = 0;
	fd = malloc(sizeof(int*));
	fd[0] = malloc(sizeof(int) * 2);
	while (mini->type[i] == '<')
	{
		fd_file = open(ft_strtrim(mini->args2[i + mini->arg + 1], " "),
		O_RDONLY, S_IRWXU);
		i++;
	}
	if (mini->type[i] == '|')
		pipe(fd[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_file, 0);
		close(fd_file);
		if (mini->type[i] == '>' || mini->type[i] == ',')
			dup2(ft_open_file(mini, i), 1);
		if (mini->type[i] == '|')
		{
			close(fd[0][0]);
			dup2(fd[0][1], 1);
			close(fd[0][1]);
		}
		ft_exe(mini->commands[0], mini->commands, env);
	}
	else
		wait(NULL);
	if (mini->type[i] == '|')
	{
		mini->type = mini->type + i;
		mini->arg = mini->arg + i + 1;
		mini->commands = ft_split(mini->args2[mini->arg], ' ');
		pid = fork();
		if (pid == 0)
		{
			close(fd[0][1]);
			dup2(fd[0][0], 0);
			close(fd[0][0]);
			ft_exe(mini->commands[0], mini->commands, env);
		}
		else
			wait(NULL);
		free(fd[0]);
	}
}

int			ft_open_file(t_args *mini, int i)
{
	int fd_file;
	i = 0;
	while (mini->type[mini->arg] == ',' || mini->type[mini->arg] == '>')
	{
		if (mini->type[mini->arg] == ',')
			fd_file = open(ft_strtrim(mini->args2[mini->arg + 1], " "),
			O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
		else
			fd_file = open(ft_strtrim(mini->args2[mini->arg + 1], " "),
			O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		mini->arg++;
	}
	return (fd_file);
}

void		ft_move_pos(t_args *mini ,int  i)
{
	int j;
	j = i;
	while (mini->type[i] == ',' || mini->type[i] == '>')
	{
		i++;
	}
	mini->type = mini->type + i;
}


void		ft_only_redir(t_args *mini, char **env)
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

void		ft_redir(t_args *mini, char **env)
{
	int pid;

	mini->commands = ft_split(mini->args2[mini->arg], ' ');
	if (mini->type[mini->arg] == ',' || mini->type[mini->arg] == '>')
		ft_only_redir(mini, env);
	else if (mini->type[mini->arg] == '<')
	{
		ft_input(mini, env);
	}
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
		ft_subpro(mini, env);
}

int			ft_subpro(t_args *mini, char **env)
{
	int	**fd;
	int	pid;
	int	i;
	int fd_file;
	int pipe_numb;

	i = 0;
	pipe_numb = 0;
	while (mini->type[pipe_numb + mini->arg] == '|')
		pipe_numb++;
	fd = malloc(pipe_numb * sizeof(int *));
	while (i < pipe_numb)
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
		mini->arg++;
		while (mini->type[mini->arg] == '|')
		{
			mini->commands = ft_split(mini->args2[mini->arg], ' ');
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
			mini->arg++;
		}
		mini->commands = ft_split(mini->args2[mini->arg], ' ');
		close(fd[i - 1][1]);
		if (i > 1)
			close(fd[i - 2][0]);
		if (mini->type[mini->arg] == '>')
			fd_file = ft_open_file(mini, i);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[i - 1][0], 0);
			close(fd[i - 1][0]);
			dup2(fd_file, 1);
			ft_exe(mini->commands[0], mini->commands, env);
		}
	}
	close(fd[0][0]);
	i = 0;
	wait(NULL);
	while (i < pipe_numb)
	{
		wait(NULL);
		free(fd[i]);
		i++;
	}
	free(fd);
	if (mini->type[mini->arg] == '|')
	{
		mini->arg++;
		ft_redir(mini, env);
	}
	return (i);
}

void		ft_read_command(char **env, t_args *mini)
{
	int		i;
	pid_t	childpid;
	char	*pwd;

	i = -1;

	while (mini->args[++i])
	{

		mini->args2 = ft_split2(mini->args[i], mini);
		mini->arg = 0;
		if (mini->type[0] == 0)
		{
			mini->commands = ft_split(mini->args2[0], ' ');
			if (!ft_strcmp("exit", mini->commands[0]))
			{
				write(1, "exit\n", 5);
				exit(0);
			}
			else if (!ft_strcmp("cd", mini->commands[0]))
			{
				if (mini->commands[1] && mini->commands[1][0] == '/')
				{
					pwd = mini->commands[1];
					if (!(opendir(pwd)))
						ft_error();
				}
				else
				{
					pwd = ft_strjoin(ft_strjoin(ft_pwd(1), "/"),
					mini->commands[1]);
					if (!(opendir(pwd)))
						ft_error();
				}
				chdir(pwd);
				continue ;
			}
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
	int		i;
	char	**env2;

	mini = malloc(sizeof(t_args));
	mini->main_chain = 0;
	mini->args = 0;
	mini->in = dup(0);
	mini->out = dup(1);
	write(1, "... ", 4);
	i = 0;
	while (env[i])
		i++;
	env2 = malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		env2[i] = ft_strdup(env[i]);
		i++;
	}
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

int			main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	ft_loop(env);
	return (0);
}
