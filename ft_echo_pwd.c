/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 19:33:04 by agianico          #+#    #+#             */
/*   Updated: 2021/03/08 19:52:39 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **argu)
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

char	*ft_pwd(int opt)
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

void	ft_echo_pwd(char **argu)
{
	if (!(ft_strcmp("echo", argu[0])))
		ft_echo(argu);
	else if (!ft_strcmp("pwd", argu[0]))
		ft_pwd(0);
	exit(0);
}
