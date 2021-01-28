/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:49:45 by antmarti          #+#    #+#             */
/*   Updated: 2021/01/28 14:58:00 by antmarti         ###   ########.fr       */
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
/*
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
}*/

void		ft_exe(char *func, char **argu, char **env)
{
	int		i;
	char	**paths;
	char	*p;
	int		j;

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

static size_t	ft_remove_char(char c, char *set)
{
	size_t		i;
	size_t		len;

	len = ft_strlen(set);
	i = 0;
	while (i < len)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	len;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (set && ft_remove_char(s1[i], (char*)set))
		i++;
	while (set && len > 1 && ft_remove_char(s1[len - 1], (char*)set))
		len--;
	if (i > len)
		len = i;
	if (!(str = (char*)malloc(sizeof(char) * (len - i + 1))))
		return (NULL);
	while (i < len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
