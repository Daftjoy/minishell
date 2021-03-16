SRCS	=	ft_split.c ft_split2.c ft_split2_expansion.c ft_strcmp.c ft_strtrim.c ft_echo_pwd.c ft_env.c ft_export.c ft_quotes.c ft_find_var.c ft_functs.c ft_unset.c \
ft_cd.c ft_exe.c ft_input.c ft_redirections.c ft_pipe.c ft_pipe2.c ft_wait.c ft_error.c ft_mini_trim.c ft_ctrl.c ft_free.c get_next_line.c get_next_line_utils.c minishell.c

OBJS =	$(SRCS:.c=.o)

FLAGS =	-Werror -Wextra -Wall

NAME =	minishell

RM = rm -f

$(NAME):
		gcc -c $(FLAGS) $(SRCS)
		gcc $(FLAGS) $(SRCS) -o $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re