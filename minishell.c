/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:30:49 by antmarti          #+#    #+#             */
/*   Updated: 2020/09/15 13:22:18 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

char			*ft_strtrim(char *s1, char const *set)
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

int				ft_strncmp(char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] && str2[i] && str1[i] == str2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}

int			ft_strrchr(char *s, int c)
{
	int i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void		ft_checkcommands(char **cmd)
{
	int i;

	i = 1;
	if (!(ft_strncmp(cmd[0], "echo", 4)))
	{
		while (cmd[i])
		{
			write(1, cmd[i], ft_strlen(cmd[i]));
			write(1, " ", 1);
			i++;
		}
		write(1, "\n", 1);
	}
}

void		ft_loop(void)
{
	char	*buffer;
	int		ret;
	int		pos;
	char	*str;
	char	**cmd;

	ret = 1;
	while (ret)
	{
		write(1, "... ", 4);
		if (!(buffer = malloc(sizeof(char) * 256)))
			break ;
		ret = read(0, buffer, 255);
		if ((pos = ft_strrchr(buffer, '\n')) >= 0)
			buffer[pos] = '\0';
		str = ft_strtrim(buffer, " ");
		cmd = ft_split(str, ' ');
		ft_checkcommands(cmd);
		free(cmd);
		free(buffer);
	}
}

int				main(void)
{
	ft_loop();
	return (0);
}
