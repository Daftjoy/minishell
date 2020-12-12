/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:49:45 by antmarti          #+#    #+#             */
/*   Updated: 2020/12/12 17:31:51 by antmarti         ###   ########.fr       */
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
	//while (p_chain[i])
	//{
	//	write(1, p_chain[i], ft_strlen(p_chain[i]));
	//	write(1, "p", 1);
	//	i++;
	//}
}

void		ft_redir(t_args *mini, char *s)
{
	int		i;
	char	**p_chain;

	mini = 0;
	i = 0;
	p_chain = ft_split(s, '>');
	//while (p_chain[i])
	//{
	//	write(1, p_chain[i], ft_strlen(p_chain[i]));
	//	write(1, "p", 1);
	//	i++;
	//}
}

void	ft_exe(char *func, char **argu, char **env)
{
	int i;
	char **paths;
	char *p;
	int	j;

	i = 0;
	j = 1;
	while (env[i])
	{
		if (!ft_strcmp("PATH", ft_substr(env[i], 0, 4)))
			paths = ft_split(env[i], ':');
		i++;
	}
	i = 0;
	while (paths[i])
	{
		p = malloc(100);
		p = ft_strjoin(paths[i], "/");
		p = ft_strjoin(p, func);
		execve(p, argu, env);
		i++;
		p = 0;
		free(p);
	}
	return ;
}

