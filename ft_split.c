/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:06:50 by antmarti          #+#    #+#             */
/*   Updated: 2021/02/19 18:03:47 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_wcount(char const *s, char c)
{
	unsigned int	n;
	unsigned int	w;
	int				i;
	int				k;

	n = 0;
	w = 0;
	i = 0;
	k = 0;
	if (ft_strchr(s, '\"'))
		while (s[i])
		{
			if (s[i] == '\"')
				k++;
			i++;
		}
	while (*(s + n))
	{
		if (*(s + n) == c)
		{
			n++;
			continue ;
		}
		w++;
		while ((*(s + n) != c) && *(s + n))
		{
			if (*(s + n) == '\"')
			{
				n++;
				while (s[n] && k > 1)
				{
					if (s[n] == '\"')
						k--;
					n++;
				}
			}
			n++;
		}
	}
	return (w);
}

static unsigned int	ft_lcount(char const *s, char c, unsigned int n)
{
	unsigned int	k;
	int				i;
	int				j;

	k = 0;
	i = 0;
	j = 0;
	if (ft_strchr(s, '\"'))
		while (s[i])
		{
			if (s[i] == '\"')
				j++;
			i++;
		}
	while (*(s + n) != c && *(s + n))
	{
		if (*(s + n) == '\"')
		{
			k++;
			while (j > 0 && s[n])
			{
				if (s[n] == '\"')
					j--;
				k++;
				n++;
			}
		}
		k++;
		n++;
	}
	return (k);
}

static unsigned int	ft_loop(char *s, char c, char **str)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;

	i = 0;
	n = 0;
	while (i < (ft_wcount(s, c)))
	{
		while (s[n] == c)
			n++;
		if (!(str[i] = (char *)malloc((ft_lcount(s, c, n) + 1) * sizeof(char))))
			return (0);
		j = 0;
		while (j < ft_lcount(s, c, n))
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

char				**ft_split(char *s, char c)
{
	char			**str;
	unsigned int	i;

	if (!s)
		return (0);
	if (!(str = (char **)malloc((ft_wcount(s, c) + 1) * sizeof(char *))))
		return (0);
	str[ft_wcount(s, c)] = NULL;
	i = ft_loop(s, c, str);
	return (str);
}
