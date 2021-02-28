/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:21:13 by antmarti          #+#    #+#             */
/*   Updated: 2021/02/25 14:10:40 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_var(char **env, char *var)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') && !ft_strcmp(var, ft_split(env[i], '=')[0]))
			str = ft_split(env[i], '=')[1];
		i++;
	}
	return (str);
}

void	ft_error(void)
{
	write(1, "Error: ", 7);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
}

char	**ft_export(char **env, char *var)
{
	int j;

	j = 0;
	while (env[j])
	{
		if (ft_strchr(env[j], '=') && ft_split(env[j], '=')
		&& (!(ft_strcmp(ft_split(env[j], '=')[0],
		ft_split(var, '=')[0]))))
		{
			free(env[j]);
			env[j] = ft_strdup(var);
			break ;
		}
		j++;
	}
	if (!env[j])
	{
		env[j] = ft_strdup(var);
		env[++j] = 0;
	}
	return (env);
}

char	**ft_parser(char **argu, char **env)
{
	int i;

	i = 1;
	while (argu[i])
	{
		if (ft_strchr(argu[i], '\"') && (!(ft_strchr(argu[i], '\'')) ||
		(ft_strchr(argu[i], '\"') < ft_strchr(argu[i], '\''))))
			argu[i] = ft_dquotes(env, argu[i], 0);
		else if (ft_strchr(argu[i], '\'') && (!(ft_strchr(argu[i], '\"')) ||
		(ft_strchr(argu[i], '\'') < ft_strchr(argu[i], '\"'))))
			argu[i] = ft_squotes(argu[i]);
		else
			argu[i] = ft_dquotes(env, argu[i], 1);
		i++;
	}
	return (argu);
}

char	*ft_dquotes(char **env, char *argu, int opt)
{
	char *str;
	char *ret;
	int i;
	int j;
	int k;

	ret = 0;
	str = malloc(ft_count(argu, 0) + 1);
	i = 0;
	k = 0;
	while (argu[i])
	{
		if (argu[i] == '$')
		{
			j = 0;
			while (argu[i + j] && argu[i + j] != ' ' && argu[i + j] != '\"'
			&& argu[i + j] != '\'')
				j++;
			str[k] = '\0';
			ret = ret ? ft_strjoin(ret, str) : ft_strdup(str);
			if (!ft_find_var(env, ft_substr(&argu[i], 1, j - 1)))
				ret = ret ? ft_strjoin(ret, ft_substr(&argu[i], 0, j)) :
				ft_substr(&argu[i], 0, j);
			else
				ret = ret ? ft_strjoin(ret, ft_find_var(env,
				ft_substr(&argu[i], 1, j - 1))) :
				ft_substr(&argu[i], 1, j - 1);
			free(str);
			str = 0;
			i += j - 1;
			str = malloc(ft_count(&argu[i], 0) + 1);
			k = 0;
		}
		else if (argu[i] != '\"' || opt)
		{
			str[k] = argu[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	ret = ret ? ft_strjoin(ret, str) : ft_strdup(str);
	free(str);
	str = 0;
	return (ret);
}

char	*ft_squotes(char *argu)
{
	char *str;
	int i;
	int k;

	i = 0;
	k = 0;
	str = malloc(ft_count(argu, 1));
	while (argu[i])
	{
		if (argu[i] != '\'')
		{
			str[k] = argu[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	return (str);
}

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

char **ft_unset(char **env, t_args *mini)
{
	int k;
	int j;

	k = 0;
	while (mini->commands[++k])
	{
		j = -1;
		while (env[++j])
			if (ft_strchr(env[j], '=') && ft_split(env[j], '=') &&
			(!(ft_strcmp(ft_split(env[j], '=')[0],
			ft_split(mini->commands[k], '=')[0]))))
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
				break ;
			}
	}
	return (env);
}

char **ft_cd(char **env, t_args *mini)
{
	char *pwd;

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
	env = ft_export(env, ft_strjoin("OLDPWD=", ft_pwd(1)));
	chdir(pwd);
	return(ft_export(env, ft_strjoin("PWD=", ft_pwd(1))));
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

char **ft_functs(char **env, t_args *mini)
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