/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:30:49 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/01 18:30:11 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_input(t_args *mini, char **env)
{
	int		fd_file;
	int		i;
	pid_t	pid;
	int		**fd;
	int		pipe_numb;

	i = 0;
	pipe_numb = 0;
	while (mini->type[mini->arg] == '<')
	{
		fd_file = open(ft_strtrim(mini->args2[mini->arg + 1], " "),
		O_RDONLY, S_IRWXU);
		mini->arg++;
	}
	if (mini->type[mini->arg] == '|')
		fd = ft_fd_creater(mini, &pipe_numb);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_file, 0);
		close(fd_file);
		if (mini->type[mini->arg] == '>' || mini->type[mini->arg] == ',')
		{
			dup2(ft_open_file(mini, mini->arg), 1);
			ft_exe(mini->commands[0], mini->commands, env);
		}
		else if (mini->type[mini->arg] == '|')
		{
			pid = fork();
			if (pid == 0)
				fd = ft_firstdup(fd, env, mini);
			else
				fd = ft_final_dup(fd, env, mini);
			close(fd[0][0]);
			ft_wait(fd, env, mini, pipe_numb);
		}
		else
			ft_exe(mini->commands[0], mini->commands, env);
	}
	else
	{
		if (!mini->type[mini->arg - 1] || !(mini->type[mini->arg - 1] == '|'))
			wait(NULL);
	}
}

int		ft_open_file(t_args *mini, int i)
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

void	ft_move_pos(t_args *mini, int i)
{
	int j;

	j = i;
	while (mini->type[i] == ',' || mini->type[i] == '>')
	{
		i++;
	}
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
		ft_pipe(mini, env);
}

int		ft_pipe(t_args *mini, char **env)
{
	int		**fd;
	pid_t	pid;
	int		pipe_numb;

	fd = ft_fd_creater(mini, &pipe_numb);
	mini->commands = ft_split(mini->args2[mini->arg], ' ');
	pid = fork();
	if (pid == 0)
		fd = ft_firstdup(fd, env, mini);
	else
		fd = ft_final_dup(fd, env, mini);
	close(fd[0][0]);
	return (ft_wait(fd, env, mini, pipe_numb));
}

void		ft_read_command(char **env, t_args *mini)
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

void		ft_loop(char **env)
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

int			main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_loop(env);
	return (0);
}
