/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:41:16 by antmarti          #+#    #+#             */
/*   Updated: 2020/11/27 17:40:00 by antmarti         ###   ########.fr       */
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
	char		*type;
}				t_args;

char			**ft_split(char *s, char c);
char			**ft_split2(char *s, t_args *mini);
int				ft_strcmp(const char *s1, const char *s2);

# endif
#endif
