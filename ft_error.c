/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:50:53 by agianico          #+#    #+#             */
/*   Updated: 2021/03/15 21:34:53 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(void)
{
	write(1, "Error: ", 7);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	g_status = 256;
}

void	ft_noargs(t_args *mini)
{
	write(1, "Error: ", 7);
	write(1, mini->commands[0], ft_strlen(mini->commands[0]));
	write(1, ": No arguments accepted", 23);
	write(1, "\n", 1);
	g_status = 256 * 3;
}

int		ft_arg_error(t_args *mini, int opt)
{
	if (!mini->type[mini->arg - 1])
	{
		write(1, "Error: ", 7);
		write(1, mini->commands[0], ft_strlen(mini->commands[0]));
		if (opt)
			write(1, ": Command not found", 19);
		else
		{
			if (mini->commands[1])
			{
				write(1, ": ", 2);
				write(1, mini->commands[1], ft_strlen(mini->commands[1]));
			}
			write(1, ": No such file or directory", 27);
		}
		write(1, "\n", 1);
	}
	if (opt)
		g_status = 127;
	else
		g_status = 256;
	return (g_status);
}

int		ft_pipe_error(t_args *mini)
{
	if (g_status > 256)
	{
		write(1, "Error: ", 7);
		write(1, mini->commands[0], ft_strlen(mini->commands[0]));
		if (g_status == 127 * 256)
			write(1, ": Command not found", 19);
		else if (g_status == 256 * 2)
		{
			write(1, ": ", 2);
			write(1, mini->commands[1], ft_strlen(mini->commands[1]));
			write(1, ": No such file or directory", 27);
			g_status /= 2;
		}
		else
			write(1, ": No arguments accepted", 23);
		write(1, "\n", 1);
	}
	return (g_status);
}
