#include "tests_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For UINT_MAX

void uint_test(const char *desc, unsigned int value)
{
    char expected_str[64];
    snprintf(expected_str, sizeof(expected_str), "%u", value);

    char *got_str = ft_print_uint(value);  // Replace with your actual unsigned int print function
    if (!got_str)
    {
        printf(RED "%s: FAIL (NULL output)\n" RESET, desc);
        return;
    }

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

void run_uint_tests(void)
{
    uint_test("Zero", 0u);
    uint_test("One", 1u);
    uint_test("Ten", 10u);
    uint_test("Max unsigned int", UINT_MAX);
    uint_test("Large number", 4000000000u);
    uint_test("Near max boundary", UINT_MAX - 1);
    uint_test("Power of 10", 1000000000u);
    uint_test("Mid range", 2147483648u);  // 2^31
    printf("\n");
}
