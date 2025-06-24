#include "test_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define EPSILON_LDOUBLE 1e-15  // Stricter tolerance for long double

void long_double_test(const char *desc, long double value, int precision)
{
    char format[32];
    char expected_str[512];
    snprintf(format, sizeof(format), "%%.%dLf", precision);
    snprintf(expected_str, sizeof(expected_str), format, value);

    char *got_str = ft_print_long_double(value, precision);  // Your custom function
    if (!got_str)
    {
        printf(RED "%s: FAIL (NULL output)\n" RESET, desc);
        return;
    }

    if (value == LDBL_MAX || value == -LDBL_MAX ) {
        printf(YELLOW "SKIP " RESET "%s (LDBL_MAX too large for string comparison)\n", desc);
        free(got_str);
        return;
    }

    // Convert strings to long double
    long double expected_val = strtold(expected_str, NULL);
    long double got_val = strtold(got_str, NULL);

    if (isnan(value)) {
        if (isnan(got_val)) {
            printf(GREEN " OK  " RESET "%s\n", desc);
        } else {
            printf(RED "FAIL" RESET " %s\n", desc);
            printf("  Expected: \"%s\" (NaN)\n", expected_str);
            printf("  Got     : \"%s\"\n", got_str);
        }
    } else if (isinf(value)) {
        if (isinf(got_val) && signbit(got_val) == signbit(value)) {
            printf(GREEN " OK  " RESET "%s\n", desc);
        } else {
            printf(RED "FAIL" RESET " %s\n", desc);
            printf("  Expected: \"%s\" (Inf)\n", expected_str);
            printf("  Got     : \"%s\"\n", got_str);
        }
    }
    else if (fabsl(got_val - expected_val) <= EPSILON_LDOUBLE * fabsl(expected_val ? expected_val : 1.0L)) {
        printf(GREEN " OK  " RESET "%s\n", desc);
    }
    else {
        printf(RED "FAIL" RESET " %s\n", desc);
        printf("  Expected: \"%s\"\n", expected_str);
        printf("  Got     : \"%s\"\n", got_str);
        printf("  Diff    : %.18Lf\n", fabsl(got_val - expected_val));
    }

    free(got_str);
}

void run_long_double_tests(void)
{
    long_double_test("Zero", 0.0L, 18);
    long_double_test("One", 1.0L, 18);
    long_double_test("Pi", 3.141592653589793238L, 18);
    long_double_test("Negative Pi", -3.141592653589793238L, 18);
    long_double_test("Big number", 1234567890123.1234567890123L, 12);
    long_double_test("Small number", 0.000000000123456789L, 18);
    long_double_test("Negative small", -0.000000000123456789L, 18);
    long_double_test("Very small (subnormal)", 1e-4930L, 18);  // small LDBL subnormal
    long_double_test("LDBL_MAX", LDBL_MAX, 18);
    long_double_test("LDBL_MIN", LDBL_MIN, 18);
    long_double_test("LDBL_EPSILON", LDBL_EPSILON, 20);
    long_double_test("Rounding", 1.999999999999999999L, 18);
    long_double_test("Half rounding", 1.555555555555555555L, 18);
    long_double_test("Negative Zero", -0.0L, 18);
    long_double_test("Positive Infinity", INFINITY, 18);
    long_double_test("Negative Infinity", -INFINITY, 18);
    long_double_test("NaN", NAN, 18);
    long_double_test("Just below 1.0", 0.999999999999999999L, 18);
    long_double_test("Just above 1.0", 1.000000000000000001L, 18);
    long_double_test("Many decimals", 3.141592653589793238462643383279L, 20);
    long_double_test("Many decimals (neg)", -2.718281828459045235360287471352L, 20);
    printf("\n");
}
