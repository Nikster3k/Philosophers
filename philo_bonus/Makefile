NAME = philo_bonus
COMPILER = cc
FLAGS = -Wall -Werror -Wextra -pthread -g
OBJ_FOLDER = objs/

SRCS =	main.c utils.c time.c philo.c philo_utils.c\
		initialize_philosophers.c print_multi.c\

OBJS = $(addprefix $(OBJ_FOLDER), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FOLDER) $(OBJS)
	$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)%.o: %.c
	$(COMPILER) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
