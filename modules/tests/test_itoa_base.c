
#include "libft.h"

#include <stdio.h>
#include <stdlib.h>

// Declare your itoa base function here or include your header
char *ft_itoa_base(int n, const char *base, int *length);

// Utility to print test results
void test_itoa_base(int n, const char *base, const char *base_name)
{
    int length = 0;
    char *result = ft_itoa_base(n, base, &length);
    if (result == NULL)
    {
        printf("Error: Invalid base or allocation failed.\n");
        return;
    }
    printf("Number: %d, Base: %s -> Result: %s, Length: %d\n", n, base_name, result, length);
    free(result);
}

int main()
{
    // Common bases
    const char *bin = "01";
    const char *oct = "01234567";
    const char *dec = "0123456789";
    const char *hex_l = "0123456789abcdef";
    const char *hex_u = "0123456789ABCDEF";

    // Test values including edge cases
    int test_values[] = {0, 1, -1, 42, -42, 2147483647, -2147483648};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (int i = 0; i < num_tests; i++)
    {
        int val = test_values[i];
        test_itoa_base(val, dec, "decimal");
        test_itoa_base(val, bin, "binary");
        test_itoa_base(val, oct, "octal");
        test_itoa_base(val, hex_l, "hex lowercase");
        test_itoa_base(val, hex_u, "hex uppercase");
        printf("\n");
    }

    // Test invalid bases
    printf("Testing invalid base (empty):\n");
    test_itoa_base(123, "", "empty base");

    printf("Testing invalid base (single char):\n");
    test_itoa_base(123, "0", "single char base");

    printf("Testing invalid base (duplicate chars):\n");
    test_itoa_base(123, "001", "duplicate chars base");

    return 0;
}
