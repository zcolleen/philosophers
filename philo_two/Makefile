NAME = philo_two

CC = gcc

FLAGS = -Wall -Wextra -Werror

HEADER = philo_two.h

SRCS = init_two.c parce_two.c philo_two.c sim_two.c string_out_two.c

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