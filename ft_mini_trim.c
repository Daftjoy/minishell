/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_trim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:31:41 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/16 14:32:25 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_trim_counter(char *str)
{
	int i;
	int j;
	int opt;
	int k;

	i = 0;
	j = 0;
	k = 0;
	opt = 0;
	while (str[i])
	{
		if (str[i] != ' ' && !opt && str[i] > 0)
			opt = 1;
		if (opt)
			j++;
		i++;
	}
	return (j);
}

char	*ft_mini_trim(char *str)
{
	int		i;
	int		j;
	int		k;
	int		opt;
	char	*ret;

	j = ft_trim_counter(str);
	ret = malloc(j + 1);
	i = 0;
	k = 0;
	opt = 0;
	while (str[i])
	{
		if (str[i] != ' ' && !opt && str[i] > 0)
			opt = 1;
		if (opt)
		{
			ret[k] = str[i];
			k++;
		}
		i++;
	}
	ret[k] = '\0';
	return (ret);
}
