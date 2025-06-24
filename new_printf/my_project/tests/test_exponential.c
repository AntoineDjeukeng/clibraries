#include "test_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON_EXP 1e-12  // tolerance for scientific format comparisons
void exponential_test(const char *desc, double value, int precision)
{
    char format[16];
    char expected_str[256];
    snprintf(format, sizeof(format), "%%.%de", precision);  // Exponential format
    snprintf(expected_str, sizeof(expected_str), format, value);  // Expected result

    char *got_str;  // Your function
    got_str=NULL;
    got_str = ft_print_exponential(value, precision);  // Your function
    if (!got_str)
    {
        printf(RED "FAIL" RESET " %s: NULL output\n", desc);
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
void run_exponential_tests(void)
{
    exponential_test("Zero", 0.0, 6);
    exponential_test("Negative zero", -0.0, 6);
    exponential_test("One", 1.0, 6);
    exponential_test("Pi", 3.1415926535, 6);
    exponential_test("Big", 12345678.9, 4);
    exponential_test("Small", 0.0000012345, 8);
    exponential_test("Negative Small", -0.0000012345, 8);
    exponential_test("Infinity", INFINITY, 6);
    exponential_test("Negative Infinity", -INFINITY, 6);
    exponential_test("NaN", NAN, 6);
    exponential_test("Just above 1", 1.000001, 6);
    exponential_test("Very small", 1e-308, 6);
    exponential_test("Very big", 1e308, 4);
    printf("\n");
}
