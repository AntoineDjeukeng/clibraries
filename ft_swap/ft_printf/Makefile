NAME = libftprintf.a

# Single source file list including ft_flags.c
SRCS = ft_calloc.c ft_input_string.c ft_isdigit.c ft_itoa_hex_split.c \
	ft_itoa_int_split.c ft_itoa_uint_split.c ft_pad_string.c ft_printf.c \
	ft_printf_hex.c ft_printf_int.c ft_printf_percent.c ft_printf_ptr.c \
	ft_printf_str.c ft_printf_uint.c ft_strchr.c ft_strdup.c ft_strlcpy.c \
	ft_strlen.c ft_substr.c ft_memcpy.c ft_pad_string_hex.c ft_flags.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re



# #include "ft_printf.h"
# #include <limits.h>
# #include <stdio.h>
# #define RED     "\033[0;31m"
# #define GREEN   "\033[0;32m"
# #define YELLOW  "\033[1;33m"
# #define BLUE    "\033[1;34m"
# #define RESET   "\033[0m"


# int main(void)
# {
#     int x = 123;
#     void *ptr = &x;
    
#     printf("Pointer: %p\n", ptr);
#     ft_printf("Pointer: %p\n", ptr);

#     return 0;
# }

# # make fclean && make bonus && clang -Wall -Wextra -Werror -g3 -fsanitize=address   ft_printf_hex1.c  -L. -lftprintf -o tester && ./tester 
