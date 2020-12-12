SRCS	=	ft_split.c ft_split2.c ft_strcmp.c get_next_line.c get_next_line_utils.c minishell.c minishell_utils.c

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