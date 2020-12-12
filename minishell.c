/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:30:49 by antmarti          #+#    #+#             */
/*   Updated: 2020/12/09 18:41:19 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_read_command(char **env, t_args *mini)
{
	int		i;
	int		j;
	pid_t	childpid;

	i = -1;
	while (mini->args[++i])
	{
		mini->args2 = ft_split2(mini->args[i], mini);
		j = 0;
		while (mini->args2[j])
		{
			mini->commands = ft_split(mini->args2[j], ' ');
			childpid = fork();
			if (childpid >= 0)
			{
				if (childpid != 0)
				{
					wait(NULL);
				}
				else
					ft_exe(mini->commands[0], mini->commands, env);
			}
			j++;
		}
	}
}

void		ft_loop(char **env)
{
	t_args	*mini;

	mini = malloc(sizeof(t_args));
	mini->main_chain = 0;
	mini->args = 0;
	write(1, "... ", 4);
	while (get_next_line(0, &mini->main_chain))
	{
		mini->args = ft_split(mini->main_chain, ';');
		ft_read_command(env, mini);
		write(1, "... ", 4);
		free(mini->main_chain);
	}
}

int				main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_loop(env);
	return (0);
}
