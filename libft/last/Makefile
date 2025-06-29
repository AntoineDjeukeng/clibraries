NAME = ft_printf

# Source file groups
SRCS = ft_calloc.c ft_input_string.c ft_isdigit.c ft_itoa_hex_split.c \
	ft_itoa_int_split.c ft_itoa_uint_split.c ft_pad_string.c ft_printf.c \
	ft_printf_hex.c ft_printf_int.c ft_printf_percent.c ft_printf_ptr.c \
	ft_printf_str.c ft_printf_uint.c ft_strchr.c ft_strdup.c ft_strlcpy.c \
	ft_strlen.c ft_substr.c

MANDATORY_SRCS = ft_flags.c
BONUS_SRCS = ft_flags_bonus.c
# TESTER_SRCS = master_tester.c

# Object groups
# MANDATORY_OBJS = $(SRCS:.c=.o) $(MANDATORY_SRCS:.c=.o) $(TESTER_SRCS:.c=.o)
# BONUS_OBJS = $(SRCS:.c=.o) $(BONUS_SRCS:.c=.o) $(TESTER_SRCS:.c=.o)
MANDATORY_OBJS = $(SRCS:.c=.o) $(MANDATORY_SRCS:.c=.o)
BONUS_OBJS = $(SRCS:.c=.o) $(BONUS_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Default rule
all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) -o $(NAME)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME)

# valgrind: bonus
# 	valgrind --leak-check=full --track-origins=yes ./$(NAME)

# clean:
# 	rm -f $(SRCS:.c=.o) $(MANDATORY_SRCS:.c=.o) $(BONUS_SRCS:.c=.o) $(TESTER_SRCS:.c=.o)
clean:
	rm -f $(SRCS:.c=.o) $(MANDATORY_SRCS:.c=.o) $(BONUS_SRCS:.c=.o) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus valgrind clean fclean re
