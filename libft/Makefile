CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wrestrict

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,%.o,$(SRC_FILES))

NAME = libft

all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME).a $(OBJ_FILES)

B_FILES = $(ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c)
bonus: $(B_FILES)
	ar rcs $(NAME).a $(B_FILES)

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME).a

re: fclean all

.PHONY: all clean fclean re
