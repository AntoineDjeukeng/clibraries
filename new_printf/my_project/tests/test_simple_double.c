#include "test_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON_DOUBLE 1e-12  // smaller tolerance for double

void double_test(const char *desc, double value, int precision)
{
    char format[16];
    char expected_str[256];
    snprintf(format, sizeof(format), "%%.%df", precision);
    snprintf(expected_str, sizeof(expected_str), format, value);

    char *got_str = ft_print_double(value, precision);  // Your double printing function
    if (!got_str)
    {
        printf(RED "%s: FAIL (NULL output)\n" RESET, desc);
        return;
    }
    if (value == DBL_MAX) {
        printf(YELLOW "SKIP " RESET "%s (DBL_MAX not supported in fixed format)\n", desc);
        free(got_str);
        return;
    }
    // Convert strings to double
    double expected_val = strtod(expected_str, NULL);
    double got_val = strtod(got_str, NULL);

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
    else if (fabs(got_val - expected_val) <= EPSILON_DOUBLE * fabs(expected_val ? expected_val : 1.0)) {
        printf(GREEN " OK  " RESET "%s\n", desc);
    }
    else {
        printf(RED "FAIL" RESET " %s\n", desc);
        printf("  Expected: \"%s\"\n", expected_str);
        printf("  Got     : \"%s\"\n", got_str);
        printf("  Diff    : %.15f\n", fabs(got_val - expected_val));
    }

    free(got_str);
}

void run_double_tests(void)
{
    double_test("Zero", 0.0, 15);
    double_test("One", 1.0, 15);
    double_test("Pi", 3.141592653589793, 15);
    double_test("Negative Pi", -3.141592653589793, 15);
    double_test("Big number", 123456789.123456789, 9);
    double_test("Small number", 0.000000123456789, 15);
    double_test("Negative small", -0.000000123456789, 15);
    double_test("Very small (subnormal)", 5e-324, 15);  // smallest positive double subnormal
    double_test("DBL_MAX", DBL_MAX, 15);
    double_test("DBL_MIN", DBL_MIN, 15);
    double_test("DBL_EPSILON", DBL_EPSILON, 15);
    double_test("Rounding", 1.999999999999999, 15);
    double_test("Half rounding", 1.555555555555555, 15);
    double_test("Negative Zero", -0.0, 15);
    double_test("Positive Infinity", INFINITY, 15);
    double_test("Negative Infinity", -INFINITY, 15);
    double_test("NaN", NAN, 15);
    double_test("Just below 1.0", 0.999999999999999, 15);
    double_test("Just above 1.0", 1.000000000000001, 15);
    double_test("Many decimals", 3.14159265358979323846, 15);
    double_test("Many decimals (neg)", -2.71828182845904523536, 15);
    printf("\n");
}
