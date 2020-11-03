NAME = philo_one

CC = gcc

FLAGS = -Wall -Wextra -Werror

HEADER = philo_one.h

SRCS = init_one.c parce_one.c philo_one.c simulation_one.c string_out_one.c

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