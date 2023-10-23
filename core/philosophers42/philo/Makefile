CC					=				cc

CFLAGS				=				-Wall -Werror -Wextra

CDEPS				=				philo.h

LIBS				=				-lpthread

SRC					=				main.c free.c utils.c libft.c init.c routines.c bools.c

OBJ					=				$(SRC:.c=.o)

NAME				=				philo

TEST_ARGS			=				5 800 200 200 7

all: $(NAME)

%.o: %.c $(CDEPS)
	$(CC) $(CFLAGS) -c $<

$(NAME): $(OBJ)
	$(CC) $^ $(CFLAGS) $(LIBS) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	./$(NAME) $(TEST_ARGS)

test-leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(TEST_ARGS)

test-drd:
	valgrind --tool=drd ./$(NAME) $(TEST_ARGS);
	
test-helgrind:
	valgrind --tool=helgrind --delta-stacktrace=yes --history-level=full ./$(NAME) $(TEST_ARGS)

.PHONY: all clean fclean re test-leaks test-drd test-helgrind
