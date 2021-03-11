/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:51:00 by agianico          #+#    #+#             */
/*   Updated: 2021/03/11 16:19:39 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_exe(char *func, char **argu, char **env, t_args *mini)
{
	int		i;
	char	**paths;
	char	*join;
	char	*join2;
	char	**split;

	paths = 0;
	argu = ft_parser(argu, env, mini);
	if (argu[0][0] == '/')
		if ((execve(argu[0], argu, env)) < 0)
			exit(ft_arg_error(mini, 0));
	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			if (!ft_strcmp("PATH", ft_substr(env[i], 0, 4)))
			{
				split = ft_split(env[i], '=');
				paths = ft_split(split[1], ':');
				ft_free_arr(split);
			}
	if (!(ft_strcmp("echo", argu[0])) || !(ft_strcmp("pwd", argu[0])))
		ft_echo_pwd(argu);
	i = -1;
	while (paths[++i])
	{
		join = ft_strjoin(paths[i], "/");
		join2 = ft_strjoin(join, func);
		execve(join2, argu, env);
		free(join);
		free(join2);
	}
	i = 1;
	ft_free_arr(paths);
	if (i == 1)
		exit(ft_arg_error(mini, 1));
	return (1);
}
