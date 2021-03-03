/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:11:34 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/03 17:24:49 by antmarti         ###   ########.fr       */
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

char	*ft_dquotes2(char *ret, char **env, char *argu, int *l)
{
	int		i;
	int		j;

	j = 0;
	i = *l;
	while (argu[i + j] && argu[i + j] != ' ' && argu[i + j] != '\"'
	&& argu[i + j] != '\'')
		j++;
	if (ft_find_var(env, ft_substr(&argu[i], 1, j - 1)))
		ret = ret ? ft_strjoin(ret, ft_find_var(env,
		ft_substr(&argu[i], 1, j - 1))) :
		ft_substr(&argu[i], 1, j - 1);
	*l += j - 1;
	return (ret);
}

char	*ft_dquotes(char **env, char *argu, int opt)
{
	char	*str;
	char	*ret;
	int		i;
	int		k;

	ret = 0;
	str = malloc(ft_count(argu, 0) + 1);
	i = -1;
	k = 0;
	while (argu[++i])
		if (argu[i] == '$')
		{
			str[k] = '\0';
			ret = ret ? ft_strjoin(ret, str) : ft_strdup(str);
			ret = ft_dquotes2(ret, env, argu, &i);
			free(str);
			str = malloc(ft_count(&argu[i], 0) + 1);
			k = 0;
		}
		else if (argu[i] != '\"' || opt)
			str[k++] = argu[i];
	str[k] = '\0';
	ret = ret ? ft_strjoin(ret, str) : ft_strdup(str);
	free(str);
	return (ret);
}
