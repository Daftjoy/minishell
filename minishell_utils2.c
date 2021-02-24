/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:21:13 by antmarti          #+#    #+#             */
/*   Updated: 2021/02/24 20:43:37 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_var(char **env, char *var)
{
	int		i;
	char	*str;

	i = 0;
	str = 0;
	printf("ENTROOOOO\n");
	while (env[i])
	{
		if (!ft_strcmp(var, ft_split(env[i], '=')[0]))
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
	str = malloc(ft_count(argu, 0));
	i = 0;
	k = 0;
	while (argu[i])
	{
		if (argu[i] == '$')
		{
			j = 0;
			while (argu[i + j] != ' ' && argu[i + j] != '\"'
			&& argu[i + j] != '\'')
				j++;
			str[k] = '\0';
			ret = ret ? ft_strjoin(ret, str) : ft_strdup(str);
			if (!ft_find_var(env, ft_substr(&argu[i], 1, j - 1)))
				ret = ft_strjoin(ret, ft_substr(&argu[i], 0, j));
			else
				ret = ft_strjoin(ret, ft_find_var(env,
				ft_substr(&argu[i], 1, j - 1)));
			free(str);
			i += j - 1;
			str = malloc(ft_count(&argu[i], 0));
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
	ret = ret ? ft_strjoin(ret, str) : str;
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
	printf("%d\n", i);
	return (i);
}
