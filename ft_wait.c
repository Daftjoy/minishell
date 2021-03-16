/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:13:53 by agianico          #+#    #+#             */
/*   Updated: 2021/03/16 13:26:59 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_wait(int **fd, char **env, t_args *mini, int pipe_numb)
{
	int i;

	i = 0;
	while (i < pipe_numb)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
	if (mini->type[mini->arg] && mini->type[mini->arg] == '|')
	{
		mini->arg++;
		ft_redir(mini, env, 0);
	}
	return (i);
}
