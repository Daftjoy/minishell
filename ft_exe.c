/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:51:00 by agianico          #+#    #+#             */
/*   Updated: 2021/03/16 13:38:10 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ft_get_path(char **env)
{
	int		i;
	char	**split;
	char	**paths;

	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			if (!ft_strcmp("PATH", ft_substr(env[i], 0, 4)))
			{
				split = ft_split(env[i], '=');
				paths = ft_split(split[1], ':');
				ft_free_arr(split);
			}
	return (paths);
}

void			ft_execute(char **paths, char **argu, char **env, char *func)
{
	int		i;
	char	*join;
	char	*join2;

	i = -1;
	while (paths[++i])
	{
		join = ft_strjoin(paths[i], "/");
		join2 = ft_strjoin(join, func);
		execve(join2, argu, env);
		free(join);
		free(join2);
	}
}

int				ft_exe(char *func, char **argu, char **env, t_args *mini)
{
	char	**paths;

	paths = 0;
	argu = ft_parser(argu, env, mini);
	if (argu[0][0] == '/')
		if ((execve(argu[0], argu, env)) < 0)
		{
			ft_arg_error(mini, 0);
			exit(127);
		}
	paths = ft_get_path(env);
	if (!(ft_strcmp("echo", argu[0])) || !(ft_strcmp("pwd", argu[0])))
		ft_echo_pwd(argu);
	ft_execute(paths, argu, env, func);
	ft_free_arr(paths);
	exit(ft_arg_error(mini, 1));
	return (g_status);
}
