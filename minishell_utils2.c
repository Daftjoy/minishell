/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:21:13 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/04 16:39:29 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count(char *str, int opt)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (opt)
		while (str[i + j])
		{
			if (str[i + j] != '\'')
				i++;
			else
				j++;
		}
	else
		while (str[i + j] && str[i + j] != '$')
		{
			if (str[i + j] != '\"')
				i++;
			else
				j++;
		}
	return (i);
}

char	**ft_unset(char **env, t_args *mini)
{
	int		k;
	int		j;
	char	**split;
	char	**split_commands;

	k = 0;
	while (mini->commands[++k])
	{
		j = -1;
		while (env[++j])
		{
			split = ft_split(env[j], '=');
			split_commands = ft_split(mini->commands[k], '=');
			if (ft_strchr(env[j], '=') && split &&
			(!(ft_strcmp(split[0], split_commands[0]))))
			{
				while (env[j])
				{
					free(env[j]);
					if (env[j + 1])
						env[j] = ft_strdup(env[j + 1]);
					else
						env[j] = 0;
					j++;
				}
				ft_free_arr(split);
				ft_free_arr(split_commands);
				break ;
			}
			ft_free_arr(split);
			ft_free_arr(split_commands);
		}
	}
	return (env);
}

char	**ft_cd(char **env, t_args *mini)
{
	char *pwd;
	char *old_pwd;

	if (mini->commands[1] && mini->commands[1][0] == '/')
	{
		pwd = mini->commands[1];
		if (!(opendir(pwd)))
			ft_error();
	}
	else
	{
		pwd = ft_strjoin(ft_pwd(1), "/");
		free(pwd);
		pwd = ft_strjoin(pwd, mini->commands[1]);
		if (!(opendir(pwd)))
			ft_error();
	}
	old_pwd = ft_strjoin("OLDPWD=", ft_pwd(1));
	ft_export(env, old_pwd);
	free(old_pwd);
	chdir(pwd);
	free(pwd);
	pwd = ft_strjoin("PWD=", ft_pwd(1));
	env = ft_export(env, pwd);
	free (pwd);
	return (env);
}

void	ft_runcmmd(char **env, t_args *mini)
{
	pid_t	childpid;

	childpid = fork();
	if (childpid >= 0)
	{
		if (childpid != 0)
			wait(NULL);
		else
			ft_exe(mini->commands[0], mini->commands, env);
	}
}

char	**ft_functs(char **env, t_args *mini)
{
	int		k;

	k = 1;
	if (!(ft_strcmp("export", mini->commands[0])) && mini->commands[1])
	{
		while (mini->commands[k] && ft_strchr(mini->commands[k], '=')
		&& mini->commands[k][0] != '=')
		{
			env = ft_export(env, mini->commands[k]);
			k++;
		}
	}
	else if (!(ft_strcmp("unset", mini->commands[0])) && mini->commands[1])
		env = ft_unset(env, mini);
	else if (!ft_strcmp("exit", mini->commands[0]))
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (!ft_strcmp("cd", mini->commands[0]))
		env = ft_cd(env, mini);
	else
		ft_runcmmd(env, mini);
	return (env);
}
