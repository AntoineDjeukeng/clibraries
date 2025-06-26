#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "tests_utils.h"

void run_one_test(const char *format_str, void *value, int int_val, const char *expected_output) {
    char *result = str_my_print_id((char *)format_str, int_val, value);
    if (!result) {
        printf("FAIL: %s -> NULL\n", format_str);
        return;
    }
    if (strcmp(result, expected_output) == 0)
        printf(" OK  : %-10s → \"%s\"\n", format_str, result);
    else
        printf("FAIL : %-10s → Got \"%s\" (Expected \"%s\")\n", format_str, result, expected_output);
    free(result);
}
void run_all_tests() {
    int i = 42;
    int neg = -123;
    // unsigned int u = 4000000000U;
    // char c = 'A';
    // char *str = "hello";
    // void *ptr = str;

    run_one_test("%+06d", &i, i, "+0042");
    run_one_test("%07d", &neg, neg, "-00123");
    // run_one_test("%u", &u, u, "4000000000");
    // run_one_test("%x", &u, u, "ee6b2800");
    // run_one_test("%X", &u, u, "EE6B2800");
    // run_one_test("%#x", &u, u, "0xee6b2800");
    run_one_test("%d", &i, i, "42");
    run_one_test("%5d", &i, i, "   42");
    run_one_test("%-5d", &i, i, "42   ");
    run_one_test("%+d", &i, i, "+42");
    run_one_test("% d", &i, i, " 42");
    run_one_test("%05d", &i, i, "00042");
    run_one_test("%.3d", &i, i, "042");

    run_one_test("%d", &neg, neg, "-123");
    run_one_test("%7d", &neg, neg, "   -123");


    // run_one_test("%c", &c, c, "A");
    // run_one_test("%5c", &c, c, "    A");
    // run_one_test("%-5c", &c, c, "A    ");

    // run_one_test("%s", str, 0, "hello");
    // run_one_test("%10s", str, 0, "     hello");
    // run_one_test("%-10s", str, 0, "hello     ");

    // run_one_test("%p", &ptr, 0, "0x..."); // Just test that it returns something starting with 0x

    printf("\n");
}
