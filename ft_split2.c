/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:06:50 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/08 20:16:51 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*ft_find(char const *s)
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
	int				n;
	int				i;

	w = 1;
	str = (char *)s;
	n = 0;
	if (ft_strchr(str, '\"'))
	{
		i = 0;
		while (s[i])
		{
			if (s[i] == '\"')
				n++;
			i++;
		}
	}
	w = ft_wcount_2(s, w, n);
	return (w);
}

static unsigned int	ft_lcount(char const *s, unsigned int n)
{
	unsigned int	k;

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

static unsigned int	ft_loop(char *s, char **str, char *type, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;

	i = -1;
	while (++i < (ft_wcount(s)))
	{
		if (!(str[i] = (char *)malloc((ft_lcount(s, n) + 1) * sizeof(char))))
			return (0);
		j = -1;
		while (++j < ft_lcount(s, n))
			str[i][j] = s[n + j];
		str[i][j] = '\0';
		if (s[n + j] == '>' && s[n + j + 1] == '>')
		{
			type[i] = ',';
			n += j + 2;
		}
		else
		{
			type[i] = s[n + j];
			n += j + 1;
		}
	}
	type[i] = '\0';
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
	i = ft_loop(s, str, mini->type, 0);
	return (str);
}
