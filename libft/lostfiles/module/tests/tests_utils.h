#pragma once
#include "../libft/libft.h"
#include "../src/data_type.h"
#include "../ft_prinf.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#define RESET  "\033[0m"
#define RED    "\033[31m"
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define BLUE   "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN   "\033[36m"
#define WHITE  "\033[37m"

void run_int_tests(void);
void run_uint_tests(void);
void run_hex_tests(void);
void run_all_tests();
