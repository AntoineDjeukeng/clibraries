NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libft
LDFLAGS =  -L./libft -lft  


SRC = main.c ft_m_actions.c ft_action.c ft_quicksort.c ft_hande_input_output.c ft_move_l1.c ft_move_handellers.c ft_wrappers1.c ft_wrappers2.c verify.c\
      $(wildcard utils/*.c) \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
