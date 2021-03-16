/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antmarti <antmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:41:16 by antmarti          #+#    #+#             */
/*   Updated: 2021/03/16 14:25:55 by antmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# ifndef SYMBOLS
#  define SYMBOLS "|><"
#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 1024
#   include <sys/types.h>
#   include <errno.h>
#   include <sys/wait.h>
#   include <stdio.h>
#   include <unistd.h>
#   include <stdlib.h>
#   include <string.h>
#   include <dirent.h>
#   include <signal.h>
#   include <fcntl.h>

typedef struct	s_args
{
	char		*main_chain;
	char		**args;
	char		**args2;
	char		**commands;
	char		*type;
	int			exit_status;
	int			in;
	int			out;
	int			arg;
	int			fd;
	int			sig_int;
	int			quotes_cont;
	int			pipe_num;
}				t_args;

/*
**							MINISHELL
*/

int				ft_arg_error(t_args *mini, int opt);
char			**ft_argu(char *arg);
char			**ft_cd_error(t_args *mini, char *pwd, char **env);
int				ft_count(char *str, int opt);
char			*ft_dquotes(char **env, char *argu, int opt, t_args *mini);
char			*ft_dquotes2(char *str, char **env, char *argu, t_args *mini);
void			ft_d(int fd_file);
void			ft_env(t_args *mini, char **env);
void			ft_error(void);
int				ft_exe(char *func, char **argu, char **env, t_args *mini);
void			ft_execute(char **paths, char **argu, char **env, char *func);
int				**ft_fd_creater(t_args *mini, int *j);
void			ft_free_arr(char **arr);
void			ft_free_int(int **arr);
char			*ft_find_var(char **env, char *var);
int				**ft_firstdup(int **fd, char **env, t_args *mini);
int				**ft_final_dup(int **fd, char **env, t_args *mini);
char			**ft_final_dup2(char **env, t_args *mini, int i, int **fd);
char			*ft_find(char const *s);
char			**ft_functs(char **env, t_args *mini);
char			**ft_get_path(char **env);
t_args			*ft_init(void);
void			ft_input(t_args *mini, char **env);
void			ft_input_2(char **env, t_args *mini, int fd_file);
void			ft_input_pipe(char **env, t_args *mini, int fd_file);
char			*ft_interrogation(char *str, char *var);
int				**ft_mid_dup(int **fd, char **env, t_args *mini, int *i);
char			**ft_mid_dup2(char **env, t_args *mini, int **fd, int i);
void			ft_final_dup3(t_args *mini);
char			*ft_mini_itoa(int	num);
char			*ft_mini_trim(char *str);
char			**ft_new_env(char **env);
void			ft_noargs(t_args *mini);
int				ft_trim_counter(char *str);
void			ft_only_redir(t_args *mini, char **env);
int				ft_open_file(t_args	*mini, int i);
char			**ft_parser(char **argu, char **env, t_args *mini);
int				ft_pipe(t_args *mini, char **env);
int				ft_pipe_error(t_args *mini);
char			**ft_read_command(char **env, t_args *mini);
char			**ft_redir(t_args *mini, char **env, int opt);
void			sig_int(int code);
void			sig_quit(int code);
char			*ft_squotes(char *argu);
int				ft_wait(int **fd, char **env, t_args *mini, int pipe_numb);
int				ft_wcount_2(char const *s, unsigned int w, int n);

/*
**							BUILTINS
*/

char			**ft_builtins(t_args *mini, char **env, int *i);
char			**ft_cd(char **env, t_args *mini);
void			ft_echo(char **argu);
void			ft_echo_pwd(char **argu);
char			**ft_export(char **env, char *var);
char			*ft_pwd(int opt);
char			**ft_unset(char **env, t_args *mini);
char			**ft_unset2(char **env, int j, char **split,
				char **split_commands);

/*
**							GNL
*/

int				get_next_line(int fd, char **line);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strchr(const char *s, int c);
int				ft_checker(int fd, char **line, char **file, int ret);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
int				ft_aux(char **line);
size_t			ft_strlen(const char *s);

/*
**							LIBFT
*/

char			**ft_split(char *s, char c);
char			**ft_split2(char *s, t_args *mini);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strtrim(char const *s1, char const *set);

pid_t	g_pid;
int		g_status;
int		g_sigint;
#  endif
# endif
#endif
