/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:21:13 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/11 17:56:45 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_runcmmd(char **env, t_args *mini)
{
	g_pid = fork();
	if (g_pid >= 0)
	{
		if (g_pid != 0)
			waitpid(g_pid, &g_status, 0);
		else
			ft_exe(mini->commands[0], mini->commands, env, mini);
	}
}

char	**ft_functs(char **env, t_args *mini)
{
	int		k;

	k = 0;
	if (!(ft_strcmp("export", mini->commands[0])) && mini->commands[1])
	{
		while (mini->commands[++k] && ft_strchr(mini->commands[k], '=')
		&& mini->commands[k][0] != '=')
			env = ft_export(env, mini->commands[k]);
	}
	else if (!(ft_strcmp("unset", mini->commands[0])) && mini->commands[1])
		env = ft_unset(env, mini);
	else if (!ft_strcmp("exit", mini->commands[0]))
	{
		write(1, "exit\n", 5);
		if (mini->commands[1])
			write(1, "No arguments accepted\n", 22);
		exit(0);
	}
	else if (!ft_strcmp("cd", mini->commands[0]))
		env = ft_cd(env, mini);
	else if (!ft_strcmp("env", mini->commands[0]))
		ft_env(env);
	else if (!mini->type[0])
		ft_runcmmd(env, mini);
	else
		ft_exe(mini->commands[0], mini->commands, env, mini);
	if (mini->type[0])
		exit(g_status/256);
	return (env);
}
