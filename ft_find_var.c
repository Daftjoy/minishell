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
	if (!ft_strcmp(var, "?"))
		return (ft_strdup(mini->exit_status));
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
