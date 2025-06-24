#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../v_libft/ft_libft.h"
#include "../ft_itoa/ft_itoa.h"
#include "../../include/ft_types.h"
char *ft_pad_string(char *str, int width, char pad_char, ft_bool left_align);
char *ft_print_float(float nub, int precision);
char *ft_print_double(double nub, int precision);
char	*ft_print_long_double(long double nub, int precision);
char *ft_print_exponential(double nub, int precision);
