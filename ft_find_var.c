/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:45:32 by agianico          #+#    #+#             */
/*   Updated: 2021/03/08 19:46:15 by agianico         ###   ########.fr       */
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
	//printf("code: %d\n", mini->exit_status);
	if (!ft_strcmp(var, "?"))
		str = ft_strdup(ft_mini_atoi(mini->exit_status));
	else
		while (env[i])
		{
			split = ft_split(env[i], '=');
			if (ft_strchr(env[i], '=') && !ft_strcmp(var, split[0]))
				str = ft_strdup(split[1]);
			i++;
			ft_free_arr(split);
		}
	//printf("code nuestro: %s\n", str);
	return (str);
}

char	*ft_mini_atoi(int	num)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 10;
	j = 1;
	while (num/i > 0)
	{
		i *= 10;
		j++;
	}
	str = malloc(j);
	i /= 10;
	str [j] = '\0';
	k = 0;
	while (k < j)
	{
		//printf("intermedio: %d\n", num%i);
		str[k] = num/i + 48;
		num = num%i;
		i /= 10;
		k++;
	}
	return	(str);
}