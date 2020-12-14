/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:06:50 by antmarti          #+#    #+#             */
/*   Updated: 2020/12/14 16:54:24 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_find(char const *s)
{
	int		i;
	char	*ret;

	ret = 0;
	i = 0;
	while (SYMBOLS[i])
	{
		if (ft_strchr(s, SYMBOLS[i]) && ret == 0)
			ret = ft_strchr(s, SYMBOLS[i]);
		else if (ft_strchr(s, SYMBOLS[i]) && ret &&
		(ret > ft_strchr(s, SYMBOLS[i])))
			ret = ft_strchr(s, SYMBOLS[i]);
		i++;
	}
	return (ret);
}

static unsigned int	ft_wcount(char const *s)
{
	unsigned int	w;
	char			*str;

	w = 1;
	str = (char *)s;
	while (ft_find(str) && str)
	{
		if (!ft_strchr(str, '\"') || (ft_strchr(str, '\"') &&
		ft_strchr(str, '\"') > ft_find(str)))
		{
			str = ft_find(str) + 1;
			w++;
		}
		else
		{
			str = ft_strchr(str, '\"') + 1;
			if (!ft_strchr(str, '\"'))
				write(1, "No double quotes", 17);
			str = ft_strchr(str, '\"') + 1;
		}
	}
	return (w);
}

static unsigned int	ft_lcount(char const *s, unsigned int n)
{
	unsigned int k;

	k = 0;
	while ((((ft_find(&s[n]) > &s[n]) || !ft_find(&s[n])) && *(s + n)))
	{
		if (*(s + n) == '\"')
		{
			k++;
			while (s[++n] != '\"' && s[n])
			{
				k++;
			}
		}
		k++;
		n++;
	}
	return (k);
}

static unsigned int	ft_loop(char *s, char **str, char *type)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;

	i = 0;
	n = 0;
	while (i < (ft_wcount(s)))
	{
		if (!(str[i] = (char *)malloc((ft_lcount(s, n) + 1) * sizeof(char))))
			return (0);
		j = 0;
		while (j < ft_lcount(s, n))
		{
			str[i][j] = s[n + j];
			j++;
		}
		str[i][j] = '\0';
		type[i] = s[n + j];
		i++;
		n += j + 1;
	}
	//type[i] = '\0';
	return (i);
}

char				**ft_split2(char *s, t_args *mini)
{
	char			**str;
	unsigned int	i;

	if (!s)
		return (0);
	if (!(str = (char **)malloc((ft_wcount(s) + 1) * sizeof(char *))))
		return (0);
	str[ft_wcount(s)] = NULL;
	i = ft_loop(s, str, mini->type);
	return (str);
}
