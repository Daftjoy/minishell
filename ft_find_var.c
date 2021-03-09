/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:45:32 by agianico          #+#    #+#             */
/*   Updated: 2021/03/09 19:26:30 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_var(char **env, char *var, t_args *mini)
{
	int		i;
	char	*str;
	char	**split;

	i = 0;
	str = 0;
	if (!ft_strcmp(var, "?"))
		str = ft_strdup(ft_mini_itoa(mini->exit_status / 256));
	else
		while (env[i])
		{
			split = ft_split(env[i], '=');
			if (ft_strchr(env[i], '=') && !ft_strcmp(var, split[0]))
				str = ft_strdup(split[1]);
			i++;
			ft_free_arr(split);
		}
	return (str);
}

char	*ft_mini_itoa(int num)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 10;
	j = 1;
	while (num / i > 0)
	{
		i *= 10;
		j++;
	}
	str = malloc(j);
	i /= 10;
	str[j] = '\0';
	k = 0;
	while (k < j)
	{
		str[k] = num / i + 48;
		num = num % i;
		i /= 10;
		k++;
	}
	return (str);
}
