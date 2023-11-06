NAME = philo
COMPILER = cc
FLAGS = -Wall -Werror -Wextra -pthread -g

SRCS = main.c utils.c time.c philo.c forks.c initialize_philosophers.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus all
