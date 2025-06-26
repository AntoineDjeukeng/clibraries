#include "tests_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For INT_MAX, INT_MIN

void int_test(const char *desc, int value)
{
    char expected_str[64];
	int sign;
    snprintf(expected_str, sizeof(expected_str), "%d", value);

	sign=0;
    char *got_str = ft_print_int(value,sign);  // Replace with your actual int print function
    if (!got_str)
    {
        printf(RED "%s: FAIL (NULL output)\n" RESET, desc);
        return;
    }
	int len=ft_strlen(got_str);
	if(sign==1)
		got_str = ft_pad_string(got_str, len+1, '-', t_false);

    if (strcmp(expected_str, got_str) == 0)
    {
        printf(GREEN " OK  " RESET "%s\n", desc);
    }
    else
    {
        printf(RED "FAIL" RESET " %s\n", desc);
        printf("  Expected: \"%s\"\n", expected_str);
        printf("  Got     : \"%s\"\n", got_str);
    }

    free(got_str);
}

void run_int_tests(void)
{
    int_test("Zero", 0);
    int_test("One", 1);
    int_test("Negative one", -1);
    int_test("Ten", 10);
    int_test("Negative Ten", -10);
    int_test("INT_MAX", INT_MAX);
    int_test("INT_MIN", INT_MIN);
    int_test("Positive Power of 10", 100000);
    int_test("Negative Power of 10", -100000);
    int_test("Just below zero", -1);
    int_test("Just above zero", 1);
    int_test("Large positive", 2147483000);
    int_test("Large negative", -2147483000);
    int_test("Near rounding boundary", 999);
    int_test("Near negative rounding boundary", -999);
    int_test("Odd number", 1357);
    int_test("Even number", -2468);
    printf("\n");
}
