/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:51:00 by agianico          #+#    #+#             */
/*   Updated: 2021/03/08 19:51:01 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_exe(char *func, char **argu, char **env, t_args *mini)
{
	int		i;
	char	**paths;
	int		bool;

	paths = 0;
	bool = 0;
	argu = ft_parser(argu, env, mini);
	mini->exit_status = 0;
	if (argu[0][0] == '/')
		if ((execve(argu[0], argu, env)) < 0)
		{
			ft_error(mini);
			printf("%d\n", errno);
			exit(errno);
		}
	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			if (!ft_strcmp("PATH", ft_substr(env[i], 0, 4)))
				paths = ft_split(env[i], ':');
	if (!(ft_strcmp("echo", argu[0])) || !(ft_strcmp("pwd", argu[0])))
		ft_echo_pwd(argu);
	i = -1;
	while (paths[++i])
		if ((execve(ft_strjoin(ft_strjoin(paths[i], "/"), func),
		argu, env)) > 0)
			bool = 1;
	ft_free_arr(paths);
	if (bool == 0)
	{
		ft_arg_error(mini);
		exit(0);
	}
	return (1);
}
