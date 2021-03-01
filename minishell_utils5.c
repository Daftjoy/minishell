/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 17:58:14 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/01 18:02:39 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**ft_fd_creater(t_args *mini, int *j)
{
	int pipe_numb;
	int **fd;
	int i;

	pipe_numb = 0;
	i = 0;
	while (mini->type[pipe_numb + mini->arg] == '|')
		pipe_numb++;
	fd = malloc(pipe_numb * sizeof(int *));
	while (i < pipe_numb)
	{
		fd[i] = malloc(2 * sizeof(int));
		i++;
	}
	pipe(fd[0]);
	*j = pipe_numb;
	return (fd);
}
