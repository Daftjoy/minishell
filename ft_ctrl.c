/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:33:26 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/15 21:07:10 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (g_pid == 0)
	{
		write(1, "\b\b  ", 4);
		write(1, "\n", 1);
		write(1, "... ", 4);
	}
	else
	{
		g_sigint = 1;
		write(1, "\n", 1);
	}
	g_pid = 0;
}

void	sig_quit(int code)
{
	char num;

	num = code + 48;
	if (g_pid != 0)
	{
		g_sigint = 2;
		write(STDOUT_FILENO, "Quit: ", 6);
		write(1, &num, 1);
		write(1, "\n", 1);
	}
	else
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
	g_pid = 0;
	return ;
}
