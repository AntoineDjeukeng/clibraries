#include <stdio.h>
#include <string.h>
#include "test_utils.h"

void print_test_result(const char *desc, const char *expected, const char *got) 
{
    if (strcmp(expected, got) == 0)
        printf(GREEN " OK  " RESET "%s\n", desc);
    else {
        printf(RED "FAIL" RESET " %s\n", desc);
        printf("  Expected: \"%s\"\n", expected);
        printf("  Got     : \"%s\"\n", got);
    }
}