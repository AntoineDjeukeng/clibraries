#include "tests_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For UINT_MAX


void hex_test(const char *desc, unsigned int value, char c)
{
    char format[8];
    char expected_str[64];

    // Build format string like "%x" or "%X"
    snprintf(format, sizeof(format), "%%%c", c);
    snprintf(expected_str, sizeof(expected_str), format, value);

    char *got_str = ft_print_hex(value, c);  // Your custom hex print function
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

void run_hex_tests(void)
{
    // Lowercase tests ('x')
    hex_test("Zero (lowercase)", 0u, 'x');
    hex_test("One (lowercase)", 1u, 'x');
    hex_test("Ten (lowercase)", 10u, 'x');
    hex_test("Max unsigned int (lowercase)", UINT_MAX, 'x');        // 0xffffffff
    hex_test("Large number (lowercase)", 4000000000u, 'x');         // 0xee6b2800
    hex_test("Near max boundary (lowercase)", UINT_MAX - 1, 'x');   // 0xfffffffe
    hex_test("Power of 10 (lowercase)", 1000000000u, 'x');          // 0x3b9aca00
    hex_test("Mid range (lowercase)", 2147483648u, 'x');            // 0x80000000
    hex_test("Pattern (lowercase)", 0xdeadbeef, 'x');               // Check if hex letters are lowercase
    hex_test("Single digit F (lowercase)", 15u, 'x');               // Should be "f"
    hex_test("High bit set (lowercase)", 0x80000000, 'x');          // Test high nibble
    hex_test("All hex digits (lowercase)", 0xabcdef12, 'x');        // Test a-f
    hex_test("Upper boundary nibble (lowercase)", 0xf0000000, 'x'); // Test upper nibble

    // Uppercase tests ('X')
    hex_test("Zero (uppercase)", 0u, 'X');
    hex_test("One (uppercase)", 1u, 'X');
    hex_test("Ten (uppercase)", 10u, 'X');
    hex_test("Max unsigned int (uppercase)", UINT_MAX, 'X');
    hex_test("Large number (uppercase)", 4000000000u, 'X');
    hex_test("Near max boundary (uppercase)", UINT_MAX - 1, 'X');
    hex_test("Power of 10 (uppercase)", 1000000000u, 'X');
    hex_test("Mid range (uppercase)", 2147483648u, 'X');
    hex_test("Pattern (uppercase)", 0xdeadbeef, 'X');
    hex_test("Single digit F (uppercase)", 15u, 'X');
    hex_test("High bit set (uppercase)", 0x80000000, 'X');
    hex_test("All hex digits (uppercase)", 0xabcdef12, 'X');
    hex_test("Upper boundary nibble (uppercase)", 0xf0000000, 'X');

    printf("\n");
}
