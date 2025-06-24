#pragma once
#include "../include/libft.h"

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


void print_test_result(const char *desc, const char *expected, const char *got) ;
void run_float_tests(void);
void run_double_tests(void);
void run_long_double_tests(void);
void run_exponential_tests(void);


