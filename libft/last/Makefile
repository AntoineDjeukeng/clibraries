CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -Iinclude -MMD -MP

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))
DEP_FILES = $(OBJ_FILES:.o=.d)

NAME = ft_printf

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -f $(OBJ_FILES) $(DEP_FILES)

fclean: clean
	rm -f $(NAME)

valgrind: $(NAME)
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

re: fclean all

-include $(DEP_FILES)

.PHONY: all clean fclean re valgrind
