/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:06:50 by antmarti          #+#    #+#             */
/*   Updated: 2021/02/24 20:15:27 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ft_quotes(int doble, int single, int n, const char *s)
{
	int i;

	i = 0;
	if (s[n + i] == '\"' || s[n + i] == '\'')
	{
		if (s[n + i] == '\"')
		{
			doble = 1;
			single = 0;
		}
		else
		{
			doble = 0;
			single = 1;
		}
		i++;
		while (s[n + i] && (doble || single))
		{
			if (s[n + i] == '\"')
				doble = !doble ? 1 : doble--;
			else if (s[n + i] == '\'')
				single = !single ? 1 : single--;
			i++;
		}
	}
	return (i);
}

static unsigned int	ft_wcount(char const *s, char c)
{
	unsigned int	n;
	unsigned int	w;
	int				k;

	n = 0;
	w = 0;
	k = 0;
	while (s[n])
	{
		if (s[n] == c)
		{
			n++;
			continue ;
		}
		w++;
		while (s[n] != c && s[n])
		{
			n += ft_quotes(0, 0, n, s);
			n++;
		}
	}
	return (w);
}

static unsigned int	ft_lcount(char const *s, char c, unsigned int n)
{
	unsigned int	k;

	k = 0;
	while (s[n] != c && s[n])
	{
		k += ft_quotes(0, 0, n, s);
		n += ft_quotes(0, 0, n, s);
		n++;
		k++;
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
