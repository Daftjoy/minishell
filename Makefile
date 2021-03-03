SRCS	=	ft_split.c ft_split2.c ft_split2_expansion.c ft_strcmp.c get_next_line.c get_next_line_utils.c minishell.c minishell_utils.c minishell_utils2.c \
minishell_utils3.c minishell_utils4.c minishell_utils5.c minishell_utils6.c minishell_utils7.c

OBJS =	$(SRCS:.c=.o)

FLAGS =	-Werror -Wextra -Wall

NAME =	minishell

RM = rm -f

$(NAME):
		gcc $(FLAGS) $(SRCS) -o $(NAME)

all:	$(NAME)

clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re