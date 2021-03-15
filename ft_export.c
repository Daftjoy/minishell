/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:43:01 by agianico          #+#    #+#             */
/*   Updated: 2021/03/15 21:12:13 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_env(char **env, char *var)
{
	int		j;
	int		i;
	char	**split;
	char	**split_var;

	j = 0;
	i = 1;
	while (env[j])
	{
		split = ft_split(env[j], '=');
		split_var = ft_split(var, '=');
		if (ft_strchr(env[j], '=') && split
		&& (!(ft_strcmp(split[0], split_var[0]))))
			i = 0;
		ft_free_arr(split);
		ft_free_arr(split_var);
		j++;
	}
	return (j + i);
}

char	**ft_export(char **env, char *var)
{
	int		j;
	char	**split;
	char	**split_var;
	char	**env2;

	j = 0;
	env2 = malloc(sizeof(char *) * ft_check_env(env, var) + 1);
	while (env[j])
	{
		split = ft_split(env[j], '=');
		split_var = ft_split(var, '=');
		if (ft_strchr(env[j], '=') && split
		&& (!(ft_strcmp(split[0], split_var[0]))))
			env2[j] = ft_strdup(var);
		else
			env2[j] = ft_strdup(env[j]);
		ft_free_arr(split);
		ft_free_arr(split_var);
		j++;
	}
	if (!env[j] && j < ft_check_env(env, var))
		env2[j++] = ft_strdup(var);
	env2[j] = 0;
	ft_free_arr(env);
	return (env2);
}
