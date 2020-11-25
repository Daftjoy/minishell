/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:06:50 by antmarti          #+#    #+#             */
/*   Updated: 2020/11/25 18:06:13 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_find(char const *s)
{
	int	i;

	i = 0;
	while (SYMBOLS[i])
	{
		if (ft_strchr(s, SYMBOLS[i]))
			return (ft_strchr(s, SYMBOLS[i]));
		i++;
	}
	return (0);
}

static unsigned int	ft_wcount(char const *s)
{
	unsigned int	n;
	unsigned int	w;
	char			*str;

	n = 0;
	w = 1;
	str = (char *)s;
	while (ft_find(&str[n]))
	{
		if (ft_strchr(&str[n], '\"') < ft_find(&str[n]))
			str = ft_find(&str[n]);
		w++;
	}
	while (!(ft_find(&str[n])) && *(str + n))
	{
		if (*(str + n) == '\"')
		{
			n++;
			while (str[n] != '\"' && str[n])
				n++;
		}
		n++;
	}
	return (w);
}

static unsigned int	ft_lcount(char const *s, unsigned int n)
{
	unsigned int k;

	k = 0;
	while (!(ft_find(&s[n])) && *(s + n))
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

static unsigned int	ft_loop(char *s, char **str)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;

	i = 0;
	n = 0;
	while (i < (ft_wcount(s)))
	{
		while (ft_find(&s[n]))
			n++;
		if (!(str[i] = (char *)malloc((ft_lcount(s, n) + 1) * sizeof(char))))
			return (0);
		j = 0;
		while (j < ft_lcount(s, n))
		{
			str[i][j] = s[n + j];
			j++;
		}
		str[i][j] = '\0';
		i++;
		n += j;
	}
	return (i);
}

char				**ft_split2(char *s)
{
	char			**str;
	unsigned int	i;

	if (!s)
		return (0);
	if (!(str = (char **)malloc((ft_wcount(s) + 1) * sizeof(char *))))
		return (0);
	str[ft_wcount(s)] = NULL;
	i = ft_loop(s, str);
	return (str);
}
