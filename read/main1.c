
#include "ft_read.h"
#include <stdio.h>
#include <stdlib.h>


void free_split_result(char **result) {
    if (!result) return;
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

void print_split_result(char **result) {
    if (!result) {
        printf("NULL result\n");
        return;
    }
    printf("Split result:\n");
    for (int i = 0; result[i] != NULL; i++) {
        printf("  [%d]: \"%s\"\n", i, result[i]);
    }
}

int main() {
    char **res;

    // 1. Normal case with multiple delimiters
    res = ft_split("apple\nbanana\ncherry", '\n');
    print_split_result(res);
    free_split_result(res);

    // 2. Delimiter at start
    res = ft_split("\nstart\nmiddle\nend", '\n');
    print_split_result(res);
    free_split_result(res);

    // 3. Delimiter at end
    res = ft_split("one\ntwo\nthree\n", '\n');
    print_split_result(res);
    free_split_result(res);

    // 4. Consecutive delimiters (should create empty strings between)
    res = ft_split("a\n\nb\n\n\nc", '\n');
    print_split_result(res);
    free_split_result(res);

    // 5. No delimiter
    res = ft_split("single_line_no_delimiter", '\n');
    print_split_result(res);
    free_split_result(res);

    // 6. Empty string input
    res = ft_split("", '\n');
    print_split_result(res);
    free_split_result(res);

    // 7. String with only delimiters
    res = ft_split("\n\n\n", '\n');
    print_split_result(res);
    free_split_result(res);

    return 0;
}
