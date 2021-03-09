/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:50:53 by agianico          #+#    #+#             */
/*   Updated: 2021/03/09 20:00:06 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(void)
{
	write(1, "Error: ", 7);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	//mini->exit_status = errno;
}

int		ft_arg_error(t_args *mini, int opt)
{
	write(1, "Error: ", 7);
	write(1, mini->commands[0], ft_strlen(mini->commands[0]));
	if (opt)
		write(1, ": Command not found", 19);
	else
		write(1, ": No such file or directory", 27);
	write(1, "\n", 1);
	return (errno * 127 / 2);
}
