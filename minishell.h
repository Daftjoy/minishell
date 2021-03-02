/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:41:16 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/02 20:01:19 by antmarti         ###   ########.fr       */
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
#  include <dirent.h>
#  include <signal.h>
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
	int			arg;
	int			fd;
	int			sig_int;
	int			exit_status;
	pid_t		pid;
}				t_args;

char			**ft_split(char *s, char c);
char			**ft_split2(char *s, t_args *mini);
int				ft_strcmp(const char *s1, const char *s2);
char 			**ft_argu(char *arg);
int				ft_exe(char *func, char **argu, char **env);
void			ft_read_command(char **env, t_args *mini);
int				ft_pipe(t_args *mini, char **env);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_only_redir(t_args *mini, char **env);
int				ft_open_file(t_args	*mini, int i);
void			ft_redir(t_args *mini, char **env);
void			ft_input(t_args *mini, char **env);
char			*ft_pwd(int opt);
void			ft_error(void);
char 			**ft_export(char **env, char *var);
char			**ft_parser(char **argu, char **env);
int				ft_count(char *str, int opt);
char			*ft_squotes(char *argu);
char			*ft_dquotes(char **env, char *argu, int opt);
char			*ft_find_var(char **env, char *var);
char 			**ft_unset(char **env, t_args *mini);
char 			**ft_functs(char **env, t_args *mini);
char 			**ft_cd(char **env, t_args *mini);
void			ft_runcmmd(char **env, t_args *mini);
int				**ft_firstdup(int **fd, char **env, t_args *mini);
int				**ft_mid_dup(int **fd, char **env, t_args *mini, int *i);
int				**ft_final_dup(int **fd, char **env, t_args *mini);
int				ft_wait(int **fd, char **env, t_args *mini, int pipe_numb);
int				**ft_fd_creater(t_args *mini, int *j);
void			ft_d(int fd_file);
void			ft_input_pipe(char **env, t_args *mini, int fd_file);
void			ft_input_2(char **env, t_args *mini, int fd_file);
# endif
#endif
