NAME = philo_bonus
COMPILER = cc
FLAGS = -Wall -Werror -Wextra -pthread -g

SRCS =	main.c philo.c philo_utils.c \
		time.c utils.c initialize_philosophers.c

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

.PHONY: clean fclean re all clear
