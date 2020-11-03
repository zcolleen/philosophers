
NAME = philo_three

CC = gcc

FLAGS = -Wall -Wextra -Werror

HEADER = philo_three.h

SRCS = init_three.c parce_three.c philo_three.c simulation.c string_out_three.c

OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADER)
		$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(FLAGS) -I . $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJS)

fclean:
		rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re