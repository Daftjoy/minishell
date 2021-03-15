/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:39:32 by agianico          #+#    #+#             */
/*   Updated: 2021/03/15 21:12:52 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset2(char **env, int j, char **split, char **split_commands)
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
	return (env);
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
				env = ft_unset2(env, j, split, split_commands);
				break ;
			}
			ft_free_arr(split);
			ft_free_arr(split_commands);
		}
	}
	return (env);
}
