CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wrestrict

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))

NAME = libft

git config user.name "AntoineDjeukeng"
git config user.email "antoinedjeukeng.com"


all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME).a $(OBJ_FILES)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME).a

re: fclean all

.PHONY: all clean fclean re
