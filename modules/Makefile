# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wrestrict -O0 -g

# Source and object files
SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

# Output library name
NAME = ft_printf.a

# Default target
all: $(NAME)

$(NAME): $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

# Clean up object files
clean:
	rm -f $(OBJ_FILES)

# Clean up object files and library
fclean: clean
	rm -f $(NAME)
# +
# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
