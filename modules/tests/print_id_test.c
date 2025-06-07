#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include "libft.h"


// Dummy declaration of your custom function
// int my_printf(const char *format, ...);

// ANSI colors
#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

// Helper to redirect stdout and capture output
char *capture_my_printf(const char *format, ...)
{
    int pipefd[2];
    va_list args;
    char *buf = malloc(1024);
    if (!buf) return NULL;

    fflush(stdout);
    pipe(pipefd);
    int stdout_copy = dup(STDOUT_FILENO);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    va_start(args, format);
    int value = va_arg(args, int);
    str_my_print_id((char *)format, value);
    va_end(args);

    fflush(stdout);
    read(pipefd[0], buf, 1023);
    close(pipefd[0]);
    dup2(stdout_copy, STDOUT_FILENO);
    close(stdout_copy);

    buf[1023] = '\0'; // ensure null-terminated
    return buf;
}
void run_test(const char *desc, const char *format, int value)
{
    char expected[1024];
    snprintf(expected, sizeof(expected), format, value); // expected output from standard printf

    char *out = str_my_print_id((char *)format, value);
    if (!out) {
        printf(RED "%s: FAIL (NULL output)" RESET "\n", desc);
        return;
    }
    

    int ok = strcmp(out, expected) == 0;

    // printf("%s: ", desc);
    if (ok)
        printf(GREEN " OK " RESET );
    else {
        printf(RED " KO " RESET);
        printf(RED "FAIL" RESET "\n");
        printf("  Format  : \"%s\"\n", format);
        printf("  Value   : %d\n", value);
        printf("  Expected: \"%s\"\n", expected);
        printf("  Got     : \"%s\"\n", out);
    }

    free(out); // Important: free the memory returned by str_my_print_id
}

int main(void)
{
    run_test("Basic %d", "%d", 42);
    run_test("Basic %i", "%i", 123);
    run_test("Negative %d", "%d", -42);
    run_test("Negative %i", "%i", -123);
    run_test("Zero", "%d", 0);
    run_test("INT_MAX", "%d", INT_MAX);
    run_test("INT_MIN", "%d", INT_MIN);
    run_test("Width 5", "%5d", 42);
    run_test("Width 5 neg", "%5d", -42);
    run_test("Precision .5", "%.5d", 42);
    run_test("Precision .5 neg", "%.5d", -42);
    run_test("Precision 0 with 0", "%.0d", 0);
    run_test("Width + Precision", "%8.5d", 42);
    run_test("Width + Precision neg", "%8.5d", -42);
    run_test("Zero-padded", "%05d", 42);
    run_test("Zero-padded neg", "%05d", -42);
    run_test("Sign +", "%+d", 42);
    run_test("Sign + neg", "%+d", -42);
    run_test("Space sign", "% d", 42);
    run_test("Space sign neg", "% d", -42);
    run_test("Left justified", "%-5d", 42);
    run_test("Left justified neg", "%-5d", -42);
    run_test("Left-justified + zero", "%-05d", 42);  // "42   "
    run_test("Sign + and space", "%+ d", 42);        // "+42"
    run_test("Width and plus", "%+5d", 42);          // "  +42"
    run_test("Width and plus neg", "%+5d", -42);     // "  -42"
    run_test("Width and space", "% 5d", 42);         // "   42"
    run_test("Width and space neg", "% 5d", -42);    // "  -42"
    run_test("Zero + sign", "%+05d", 42);            // "+0042"
    run_test("Zero + sign neg", "%+05d", -42);       // "-0042"
    run_test("Precision + sign", "%+.5d", 42);       // "+00042"
    run_test("Precision + space", "% .5d", 42);      // " 00042"
    run_test("Width smaller than number", "%2d", 12345); // "12345"
    run_test("Large width/precision", "%20.15d", 123); // "     00000000000123"
    run_test("Width + Precision (i)", "%8.5i", 42);
    run_test("Zero-padded (i)", "%05i", 42);
    run_test("Sign + (i)", "%+i", 42);

    printf("\n");
    return 0;
}
