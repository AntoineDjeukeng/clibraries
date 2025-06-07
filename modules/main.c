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

    printf("\n");
    run_test("Unsigned basic", "%u", 12345);
    run_test("Octal basic", "%o", 64);             // "100"
    run_test("Octal with #", "%#o", 64);           // "0100"
    run_test("Hex lower", "%x", 255);              // "ff"
    run_test("Hex upper", "%X", 255);              // "FF"
    run_test("Hex with #", "%#x", 255);            // "0xff"
    run_test("Hex with # and upper", "%#X", 255);  // "0XFF"
    run_test("Hex width", "%8x", 255);             // "     ff"
    run_test("Hex zero padded", "%08x", 255);      // "000000ff"
    run_test("Hex width + #", "%#8x", 255);        // "   0xff"
    run_test("Octal + precision", "%.5o", 10);     // "00012"
    run_test("Octal zero with #", "%#o", 0);        // expect "0"
    run_test("Hex zero with #", "%#x", 0);          // expect "0"
    run_test("Hex upper zero with #", "%#X", 0);    // expect "0"
    run_test("Unsigned max", "%u", UINT_MAX);
    run_test("Hex max", "%x", UINT_MAX);
    run_test("Octal max", "%o", UINT_MAX);
    run_test("Precision 0 zero unsigned", "%.0u", 0); // expect ""
    run_test("Precision 0 zero octal", "%.0o", 0);    // expect ""
    run_test("Zero pad with precision and # octal", "%#08.5o", 64);  // expect "00000100" (no extra 0 prefix)
    run_test("Zero pad with precision and # hex", "%#010.5x", 255);  // expect "     000ff" or "0x000ff" depending on spec
    run_test("Width smaller than prefix+num", "%#3x", 15);  // expect "0xf"
    run_test("Left justify with # octal", "%-#6o", 10);  // expect "012   "
    run_test("Left justify with # hex", "%-#6x", 10);    // expect "0xa   "
    run_test("Negative input unsigned", "%u", -1);  // expect UINT_MAX
    run_test("Negative input hex", "%x", -1);       // expect "ffffffff" (or 64-bit equivalent)

    printf("\n");
    return 0;
}
