NAME = main.out
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -I./ft_itoa
LIBFT_IO = ft_itoa/ft_itoa.a
SRC = main.c
OBJ = $(SRC:.c=.o)
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

all: $(LIBFT_IO) $(NAME)

$(LIBFT_IO):
	make -C ft_itoa

$(NAME): $(OBJ) $(LIBFT_IO)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_IO)

valgrind: all
	$(VALGRIND) ./$(NAME)

clean:
	rm -f $(OBJ)
	make -C ft_itoa clean

fclean: clean
	rm -f $(NAME)
	make -C ft_itoa fclean

re: fclean all
