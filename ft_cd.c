/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:38:16 by agianico          #+#    #+#             */
/*   Updated: 2021/03/11 17:25:55 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_cd(char **env, t_args *mini)
{
	char	*pwd;
	char	*old_pwd;
	DIR		*error;

	if (mini->commands[1] && mini->commands[1][0] == '/')
		pwd = ft_strdup(mini->commands[1]);
	else
	{
		pwd = ft_strjoin(ft_pwd(1), "/");
		free(pwd);
		pwd = ft_strjoin(pwd, mini->commands[1]);
	}
	if ((error = opendir(pwd)) <= 0)
	{
		ft_arg_error(mini, 0);
		free(pwd);
		return (env);
	}
	closedir(error);
	old_pwd = ft_strjoin("OLDPWD=", ft_pwd(1));
	env = ft_export(env, old_pwd);
	free(old_pwd);
	chdir(pwd);
	free(pwd);
	pwd = ft_strjoin("PWD=", ft_pwd(1));
	env = ft_export(env, pwd);
	free(pwd);
	return (env);
}
