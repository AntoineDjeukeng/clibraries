NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = hach_sorting.c main.c ft_quicksort.c ft_swap_int.c
OBJ = $(SRC:.c=.o)
FT_PRINTF_LIB = ft_printf/libftprintf.a

# Compiler flags for AddressSanitizer
SANITIZE_FLAGS = -fsanitize=address -g

all: $(FT_PRINTF_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(FT_PRINTF_LIB)

$(FT_PRINTF_LIB):
	$(MAKE) -C ft_printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C ft_printf clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C ft_printf fclean
	rm -f $(NAME)

re: fclean all

# Run program with valgrind memory leak check
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# Build and run with AddressSanitizer enabled
sanitizer: CFLAGS += $(SANITIZE_FLAGS)
sanitizer: re
	./$(NAME)

.PHONY: all clean fclean re valgrind sanitizer
