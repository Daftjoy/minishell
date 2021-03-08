/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:43:01 by agianico          #+#    #+#             */
/*   Updated: 2021/03/08 19:53:11 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export(char **env, char *var)
{
	int		j;
	char	**split;
	char	**split_var;

	j = 0;
	while (env[j])
	{
		split = ft_split(env[j], '=');
		split_var = ft_split(var, '=');
		if (ft_strchr(env[j], '=') && split
		&& (!(ft_strcmp(split[0], split_var[0]))))
		{
			free(env[j]);
			env[j] = ft_strdup(var);
			ft_free_arr(split);
			ft_free_arr(split_var);
			break ;
		}
		ft_free_arr(split);
		ft_free_arr(split_var);
		j++;
	}
	if (!env[j])
	{
		free(env[j]);
		env[j] = ft_strdup(var);
		env[++j] = 0;
	}
	return (env);
}
