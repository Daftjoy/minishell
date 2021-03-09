/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:50:53 by agianico          #+#    #+#             */
/*   Updated: 2021/03/08 19:50:54 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_args *mini)
{
	write(1, "Error: ", 7);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	mini->exit_status = errno;
}

void	ft_arg_error(t_args *mini)
{
	write(1, "Error: ", 7);
	write(1, mini->commands[0], ft_strlen(mini->commands[0]));
	write(1, ": Command not found", 19);
	write(1, "\n", 1);
	mini->exit_status = 127;
}
