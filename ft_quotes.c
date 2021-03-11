/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 16:11:34 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/11 17:27:56 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**ft_parser(char **argu, char **env, t_args *mini)
{
	int i;

	i = 1;
	while (argu[i])
	{
		if (ft_strchr(argu[i], '\"') && (!(ft_strchr(argu[i], '\'')) ||
		(ft_strchr(argu[i], '\"') < ft_strchr(argu[i], '\''))))
			argu[i] = ft_dquotes(env, argu[i], 0, mini);
		else if (ft_strchr(argu[i], '\'') && (!(ft_strchr(argu[i], '\"')) ||
		(ft_strchr(argu[i], '\'') < ft_strchr(argu[i], '\"'))))
			argu[i] = ft_squotes(argu[i]);
		else
			argu[i] = ft_dquotes(env, argu[i], 1, mini);
		i++;
	}
	return (argu);
}

char	*ft_dquotes2(char *ret, char **env, char *argu, t_args *mini)
{
	int		j;

	j = 0;
	while (argu[mini->quotes_cont + j] && argu[mini->quotes_cont + j]
	!= ' ' && argu[mini->quotes_cont + j] != '\"'
	&& argu[mini->quotes_cont + j] != '\'')
		j++;
	if (ft_find_var(env, ft_substr(&argu[mini->quotes_cont], 1, j - 1)))
		ret = ret ? ft_strjoin(ret, ft_find_var(env,
		ft_substr(&argu[mini->quotes_cont], 1, j - 1))) :
		ft_substr(&argu[mini->quotes_cont], 1, j - 1);
	mini->quotes_cont += j - 1;
	return (ret);
}

char	*ft_dquotes(char **env, char *argu, int opt, t_args *mini)
{
	char	*str;
	char	*ret;
	int		k;

	ret = 0;
	str = malloc(ft_count(argu, 0) + 1);
	mini->quotes_cont = -1;
	k = 0;
	while (argu[++mini->quotes_cont])
		if (argu[mini->quotes_cont] == '$')
		{
			str[k] = '\0';
			ret = ret ? ft_strjoin(ret, str) : ft_strdup(str);
			ret = ft_dquotes2(ret, env, argu, mini);
			free(str);
			str = malloc(ft_count(&argu[mini->quotes_cont], 0) + 1);
			k = 0;
		}
		else if (argu[mini->quotes_cont] != '\"' || opt)
			str[k++] = argu[mini->quotes_cont];
	str[k] = '\0';
	ret = ret ? ft_strjoin(ret, str) : ft_strdup(str);
	free(str);
	return (ret);
}

char	*ft_squotes(char *argu)
{
	char	*str;
	int		i;
	int		k;

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
