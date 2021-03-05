/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 17:49:45 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/05 18:52:56 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_echo(char **argu)
{
	int i;
	int	opt;

	opt = 0;
	if (argu[1] && !ft_strcmp(argu[1], "-n"))
		opt = 1;
	i = opt + 1;
	if (argu[i])
	{
		write(1, argu[i], ft_strlen(argu[i]));
		i++;
	}
	while (argu[i])
	{
		write(1, " ", 1);
		write(1, argu[i], ft_strlen(argu[i]));
		i++;
	}
	if (!opt)
		write(1, "\n", 1);
}

char			*ft_pwd(int opt)
{
	char *pwd;

	pwd = malloc(100);
	getcwd(pwd, 100);
	if (opt == 0)
	{
		write(1, pwd, ft_strlen(pwd));
		write(1, "\n", 1);
	}
	free(pwd);
	return (pwd);
}

int				ft_exe(char *func, char **argu, char **env)
{
	int		i;
	char	**paths;
	int		bool;

	paths = 0;
	bool = 0;
	argu = ft_parser(argu, env);
	if (argu[0][0] == '/')
		execve(argu[0], argu, env);
	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			if (!ft_strcmp("PATH", ft_substr(env[i], 0, 4)))
				paths = ft_split(env[i], ':');
	if (!(ft_strcmp("echo", argu[0])) || !(ft_strcmp("pwd", argu[0])))
		ft_echo_pwd(argu);

	i = -1;
	while (paths[++i])
		if ((execve(ft_strjoin(ft_strjoin(paths[i], "/"), func),
		argu, env)) > 0)
			bool = 1;
	ft_free_arr(paths);
	if (bool == 0)
	{
		ft_error();
		exit(0);
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
