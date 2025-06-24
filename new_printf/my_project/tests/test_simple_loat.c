#include "test_utils.h"


#define EPSILON 1e-6  // Tolerance threshold; you may adapt based on precision

void float_test(const char *desc, float value, int precision)
{
    char format[16];
    char expected_str[128];
    snprintf(format, sizeof(format), "%%.%df", precision);
    snprintf(expected_str, sizeof(expected_str), format, value);

    char *got_str = ft_print_float(value, precision);
    if (!got_str)
    {
        printf(RED "%s: FAIL (NULL output)\n" RESET, desc);
        return;
    }

    // Try to convert both strings to floats
    float expected_val = strtof(expected_str, NULL);
    float got_val = strtof(got_str, NULL);

    // Handle NaN separately (since NaN != NaN)
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
    else if (fabsf(got_val - expected_val) <= EPSILON * fabsf(expected_val ? expected_val : 1.0f)) {
        printf(GREEN " OK  " RESET "%s\n", desc);
    }
    else {
        printf(RED "FAIL" RESET " %s\n", desc);
        printf("  Expected: \"%s\"\n", expected_str);
        printf("  Got     : \"%s\"\n", got_str);
        printf("  Diff    : %.10f\n", fabsf(got_val - expected_val));
    }

    free(got_str);
}


void run_float_tests(void)
{
    float_test("Zero", 0.0f, 6);
    float_test("One", 1.0f, 6);
    float_test("Pi", 3.141592f, 6);
    float_test("Negative Pi", -3.141592f, 6);
    float_test("Big number", 123456.789f, 3);
    float_test("Small number", 0.000123f, 6);
    float_test("Negative small", -0.000123f, 6);
    float_test("Very small (subnormal)", 1e-38f, 8);
    float_test("FLT_MAX", FLT_MAX, 20);
    float_test("FLT_MIN", FLT_MIN, 6);
    float_test("FLT_EPSILON", FLT_EPSILON, 10);
    float_test("Rounding", 1.999999f, 5);
    float_test("Half rounding", 1.55555f, 3);
    float_test("Negative Zero", -0.0f, 6);
    float_test("Positive Infinity", INFINITY, 6);
    float_test("Negative Infinity", -INFINITY, 6);
    float_test("NaN", NAN, 6);
    float_test("Subnormal", 1.401298e-45f, 8);
    float_test("Just below 1.0", 0.9999999f, 7);
    float_test("Just above 1.0", 1.000001f, 7);
    float_test("Many decimals", 3.1415926535f, 9);
    float_test("Many decimals (neg)", -2.7182818284f, 9);
    printf("\n");
}
