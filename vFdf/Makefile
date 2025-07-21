NAME = mlx_image_test
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./minilibx -I./libft -I./reference -I./transform -I./data
LDFLAGS = -L./minilibx -lmlx -lXext -lX11 -lm -lbsd -L./libft -lft  

SRC = main.c \
      $(wildcard data/*.c) \
      $(wildcard reference/*.c) \
      $(wildcard transform/*.c) \
      $(wildcard events/*.c) 

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
