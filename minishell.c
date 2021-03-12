/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 19:23:38 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/11 17:45:00 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_read_command(char **env, t_args *mini)
{
	int		i;

	i = -1;
	while (mini->args[++i])
	{
		mini->args2 = ft_split2(mini->args[i], mini);
		mini->arg = 0;
		env = ft_redir(mini, env);
		ft_free_arr(mini->args2);
	}
	return (env);
}

void	ft_loop(char **env)
{
	t_args	*mini;
	int		i;
	char	**env2;
	char	**split;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	mini = malloc(sizeof(t_args));
	mini->main_chain = 0;
	mini->args = 0;
	write(1, "... ", 4);
	i = 0;
	while (env[i])
		i++;
	env2 = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (env[++i])
	{
		env2[i] = ft_strdup(env[i]);
		split = ft_split(env[i], '=');
		if (!ft_strcmp(split[0], "SHLVL"))
			env2[i][6] += 1;
		ft_free_arr(split);
	}
	env2[i] = 0;
	while (get_next_line(0, &mini->main_chain) > 0)
	{
		mini->args = ft_split(mini->main_chain, ';');
		if (mini->args && !g_sigint)
		{
			env2 = ft_read_command(env2, mini);
			ft_free_arr(mini->args);
		}
		write(1, "... ", 4);
		free(mini->main_chain);
		if (g_sigint == 1)
			g_status = 256 * 130;
		else if (g_sigint == 2)
			g_status = 256 * 131;
		g_sigint = 0;
		g_pid = 0;
	}
	write(1, "exit\n", 5);
	free(mini);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	ft_loop(env);
	return (0);
}
