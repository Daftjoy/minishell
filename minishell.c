/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:30:49 by antmarti          #+#    #+#             */
/*   Updated: 2020/11/25 18:05:01 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pipe(t_args *mini, char *s)
{
	int		i;
	char	**p_chain;

	mini = 0;
	i = 0;
	p_chain = ft_split(s, '|');
	while (p_chain[i])
	{
		write(1, p_chain[i], ft_strlen(p_chain[i]));
		write(1, "p", 1);
		i++;
	}
}

void		ft_redir(t_args *mini, char *s)
{
	int		i;
	char	**p_chain;

	mini = 0;
	i = 0;
	p_chain = ft_split(s, '>');
	while (p_chain[i])
	{
		write(1, p_chain[i], ft_strlen(p_chain[i]));
		write(1, "p", 1);
		i++;
	}
}

void		ft_loop(void)
{
	t_args	*mini;
	int		status;
	int i;
	int j;

	mini = malloc(sizeof(t_args));
	mini->main_chain = 0;
	mini->args = 0;
	status = 1;
	i = 0;
	write(1, "... ", 4);
	while (status)
	{
		get_next_line(0, &mini->main_chain);

		mini->args = ft_split(mini->main_chain, ';');
		i = 0;
		while (mini->args[i])
		{
			//mini->args2 = ft_split(mini->args[i], ' ');
			mini->args2 = ft_split2(mini->args[i]);
			j = 0;
			while (mini->args2[j])
			{
				write(1, mini->args2[j], ft_strlen(mini->args2[j]));
				write(1, " ", 1);
				j++;
			}
			write(1, "\n", 1);
			i++;
		}
		//status = ft_execute(args);
		write(1, "... ", 4);
		free(mini->main_chain);
	}
}

int				main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	ft_loop();
	return (0);
}
