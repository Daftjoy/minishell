/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agianico <agianico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:41:16 by antmarti          #+#    #+#             */
/*   Updated: 2020/12/14 18:40:19 by agianico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef SYMBOLS
#  define SYMBOLS "|><"
#  include <sys/types.h>
#  include <errno.h>
#  include <sys/wait.h>
#  include <stdio.h>
#  include <unistd.h>
#  include <stdlib.h>
#  include <string.h>
#  include "get_next_line.h"

typedef struct	s_args
{
	char		*main_chain;
	char		**args;
	char		**args2;
	char		**commands;
	char		*type;
	int			in;
	int			out;
}				t_args;

char			**ft_split(char *s, char c);
char			**ft_split2(char *s, t_args *mini);
int				ft_strcmp(const char *s1, const char *s2);
char 			**ft_argu(char *arg);
void			ft_exe(char *func, char **argu, char **env);
void			ft_read_command(char **env, t_args *mini);
void			ft_subpro(t_args *mini, char **env);

# endif
#endif
