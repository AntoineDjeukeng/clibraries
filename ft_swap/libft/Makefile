NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wrestrict

LIB_SRCS := $(filter-out main.c, $(wildcard *.c)) \
            $(wildcard ft_printf/*.c) \
            $(wildcard get_next_line/*.c)

LIB_OBJS := $(LIB_SRCS:.c=.o)
TEST_SRC := main.c
TEST_OBJS := $(TEST_SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIB_OBJS)
	ar rcs $(NAME) $(LIB_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L. -lft -o test_ft

clean:
	rm -f $(LIB_OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) test_ft

re: fclean all

.PHONY: all clean fclean re test
