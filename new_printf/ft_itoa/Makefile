# **************************************************************************** #
#                                  ft_itoa Makefile                            #
# **************************************************************************** #


NAME = ft_itoa.a
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

