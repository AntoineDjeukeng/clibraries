# Existing executable
NAME = push_swap
# Bonus executable
BONUS_NAME = checker_linux
 
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libft
LDFLAGS = -L./libft -lft  

# Source files
SRC = ft_m_actions.c ft_action.c ft_quicksort.c ft_hande_input_output.c ft_move_l1.c  ft_move_handellers.c ft_wrappers1.c ft_wrappers2.c ft_sort.c\
      $(wildcard utils/*.c) \
# Normal build uses main.c
SRCS_MAIN = main.c $(SRC)
OBJS_MAIN = $(SRCS_MAIN:.c=.o)

# Bonus build uses main_bonus.c instead of main.c
SRCS_BONUS = main_bonus.c  verify.c $(SRC)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

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
