/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:49:45 by antmarti          #+#    #+#             */
/*   Updated: 2021/02/08 17:59:36 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_args *mini, char **env)
{
	char *s;
	int	opt;

	opt = 0;
	s = ft_strtrim(ft_substr(mini->args2[mini->arg], 5,
	ft_strlen(mini->args2[mini->arg]) - 5), " ");
	if (s[0] == '-' && s[1] == 'n')
	{
		opt = 1;
		s = s + 2;
		s = ft_strtrim(s, " ");
	}
	write(1, s, ft_strlen(s));
	env = 0;
	if (!opt)
		write(1, "\n", 1);
	free(s);
}

int		ft_exe(char *func, char **argu, char **env, t_args *mini)
{
	int		i;
	char	**paths;
	char	*p;

	i = 0;

	if (argu[0][0] == '/')
		execve(argu[0], argu, env);
	if (!ft_strcmp("echo", argu[0]))
	{
		ft_echo(mini, env);
		exit(0);
	}
	while (env[i])
	{
		if (argu[1] && (argu[1][0] == '$' ||
		(argu[1][0] == '\"' && argu[1][1] == '$')))
		{
			if (argu[1][1] == '$')
				if (!ft_strcmp(ft_substr(argu[1], 2, ft_strlen(argu[1]) - 3),
				ft_split(env[i], '=')[0]))
					argu[1] = ft_split(env[i], '=')[1];
			if (!ft_strcmp(ft_substr(argu[1], 1, ft_strlen(argu[1]) - 1),
			ft_split(env[i], '=')[0]))
				argu[1] = ft_split(env[i], '=')[1];
		}
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
	return (1);
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
	len =ft_strlen(s1);
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
