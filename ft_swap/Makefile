NAME        = push_swap
BONUS_NAME  = checker

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror \
              -I./libft \
              -I./utils \
              -I./data
LDFLAGS     = -L./libft -lft

LIBFT_DIR   = ./libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

SRC         = $(wildcard data/*.c) \
              $(wildcard utils/*.c) \
              $(wildcard save/*.c)

SRCS_MAIN   = main.c $(SRC)
OBJS_MAIN   = $(SRCS_MAIN:.c=.o)

SRCS_BONUS  = main_bonus.c help_bonus.c $(SRC)
OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

# Default rule
all: $(NAME)

$(NAME): $(OBJS_MAIN) $(LIBFT_LIB)
	$(CC) $(OBJS_MAIN) $(LDFLAGS) -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_BONUS) $(LIBFT_LIB)
	$(CC) $(OBJS_BONUS) $(LDFLAGS) -o $@

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_MAIN) $(OBJS_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re


# ARG=$(python3 -c "import random; print(' '.join(map(str, random.sample(range(-300, 300), 600))))")
