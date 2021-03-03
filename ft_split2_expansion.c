/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:03:11 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/03 16:16:57 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wcount_2(char const *s, unsigned int w, int n)
{
	char *str;

	str = (char *)s;
	while (ft_find(str) && str)
	{
		if (!ft_strchr(str, '\"') || (ft_strchr(str, '\"') &&
					ft_strchr(str, '\"') > ft_find(str)))
		{
			if (ft_find(str)[0] == '>' && ft_find(str)[1] == '>')
				str = ft_find(str) + 2;
			else
				str = ft_find(str) + 1;
			w++;
		}
		else
		{
			while (n > 0 && ft_strchr(str, '\"') < ft_find(str))
			{
				str = ft_strchr(str, '\"') + 1;
				n--;
			}
		}
	}
	return (w);
}
