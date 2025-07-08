#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// ------------------ FLAG STRUCT --------------------


#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

// Use a large enough buffer
#define BUF_SIZE 1000

void compare_printfs(const char *format, ...)
{
    char std_buf[BUF_SIZE];
    char ft_buf[BUF_SIZE];
    memset(std_buf, 0, BUF_SIZE);
    memset(ft_buf, 0, BUF_SIZE);

    // First capture standard printf output to buffer
    va_list args1, args2;
    va_start(args1, format);
    va_copy(args2, args1);
    int std_len = vsnprintf(std_buf, sizeof(std_buf), format, args1);
    va_end(args1);

    // Set up pipe to capture ft_printf output
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    // Save original stdout
    int stdout_fd = dup(STDOUT_FILENO);
    if (stdout_fd == -1) {
        perror("dup");
        return;
    }

    // Redirect stdout to pipe
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    // Call ft_printf with format and arguments
    int ft_len = ft_printf(format, args2);
    va_end(args2);

    // Restore original stdout
    fflush(stdout);
    dup2(stdout_fd, STDOUT_FILENO);
    close(stdout_fd);

    // Read ft_printf output from pipe
    read(pipefd[0], ft_buf, BUF_SIZE - 1);
    close(pipefd[0]);

    // Print and compare
    printf("FORMAT: \"%s\"\n", format);
    printf("STD   : \"%s\" (len = %d)\n", std_buf, std_len);
    printf("FT    : \"%s\" (len = %d)\n", ft_buf, ft_len);

    if (strcmp(std_buf, ft_buf) != 0 || std_len != ft_len) {
        printf("❌ Mismatch detected!\n\n");
    } else {
        printf("✅ Match OK\n\n");
    }
}

void f_check(int measured_len, int expected_len, const char *test_desc)
{
	measured_len -=3;
    if (measured_len == expected_len)
        printf("OK   - %s (measured: %d, expected: %d)\n", test_desc, measured_len, expected_len);
    else
        printf("DIFF - %s (measured: %d, expected: %d)\n", test_desc, measured_len, expected_len);
}

int main(void)
{
    // compare_printfs("Hello %s! Number: %d, Hex: %#x\n", "world", 42, 42);
    // compare_printfs("Zero-padded: %08d\n", 123);
    // compare_printfs("Left-align: %-10s Done.\n", "text");
    // compare_printfs("Precision: %.5s\n", "abcdefg");
    // compare_printfs("Hex: %x %X\n", 255, 255);
    // compare_printfs("Pointer: %p\n", (void *)main);
    // compare_printfs("Char: %c End.\n", 'A');
    // ft_printf("Hello %s! Number: %d, Hex: %#x\n", "world", 42, 42);
    // ft_printf("Zero-padded: %08d\n", 123);
    // ft_printf("Left-align: %-10s Done.\n", "text");
    // ft_printf("Precision: %.5s\n", "abcdefg");
    // ft_printf("Hex: %x %X\n", 255, 255);
    // ft_printf("Pointer: %p\n", (void *)main);
	// printf("derictly from my code \n");
    // int i =ft_printf("Char: %c End.\n", 'A');
	// printf("len = %d\n",i);

	// ft_printf("[%030.20X]\n", -1);
	// printf("[%030.20X]\n", -1);
	// ft_printf("%01.0X", 0);
	// printf("\n");
	// printf("%c",' ');
	// char *gar;
	// int i1=ft_printf("[%5c now you see", '\0');
	// printf("] %d\n[",i1-1);
	// int i2=printf("%5c now you see", '\0');
	// printf("] %d\n",i2);
	// char *null_str = NULL;
    // f_check(ft_printf("[%d]\n", 42), 2, "Basic integer printing: 42");           // "42" length=2
    // f_check(ft_printf("[%i]\n", -42), 3, "Basic integer printing: -42");          // "-42" length=3

    // f_check(ft_printf("[%5d]\n", 42), 5, "Width 5, right aligned");               // 3 spaces + "42" length=5
    // f_check(ft_printf("[%-5d]\n", 42), 5, "Width 5, left aligned");               // "42" + 3 spaces length=5

    // f_check(ft_printf("[%.5d]\n", 42), 5, "Precision 5 pads zeros");              // "00042" length=5
    // f_check(ft_printf("[%.0d]\n", 0), 0, "Precision 0 and zero value prints empty"); // empty

    // f_check(ft_printf("[%8.5d]\n", 42), 8, "Width 8, precision 5, right aligned"); // 3 spaces + "00042" length=8
    // f_check(ft_printf("[%-8.5d]\n", 42), 8, "Width 8, precision 5, left aligned");  // "00042" + 3 spaces length=8

    // f_check(ft_printf("[%05d]\n", 42), 5, "Zero padding width 5");                 // "00042" length=5

    // f_check(ft_printf("[%08.5d]\n", 42), 8, "Zero padding ignored with precision"); // note: 3 chars subtracted due to "10:"?

    // f_check(ft_printf("[%5.0d]\n", 0), 5, "Width 5, precision 0, zero val → spaces"); // 5 spaces length=5
    // f_check(ft_printf("[%-5.0d]\n", 0), 5, "Width 5 left aligned zero val empty");  // same 5 spaces

    // f_check(ft_printf("[%+d]\n", 42), 3, "Plus flag");                            // "+42" length=3
    // f_check(ft_printf("[% d]\n", 42), 3, "Space flag");                           // " 42" length=3
    // f_check(ft_printf("[%+5d]\n", 42), 5, "Plus flag with width 5");              // "  +42" length=5
    // f_check(ft_printf("[% 5d]\n", 42), 5, "Space flag with width 5");             // "   42" length=5

    // f_check(ft_printf("[%8.5d]\n", -42), 8, "Negative number, width 8, precision 5"); // "  -00042" length=8
    // f_check(ft_printf("[%-8.5d]\n", -42), 8, "Negative number, left aligned");      // "-00042  " length=8
    // f_check(ft_printf("[%-15.d\n]", 0), 15, "Negative number, left aligned");      // "-00042  " length=8
	// // ft_printf("[%-10.X\n]", 0);
	// f_check(ft_printf("[%.5s]\n", null_str),0 , "momo");
	// f_check(ft_printf("[%.7s]\n", null_str),0 , "momo");
	// f_check(ft_printf("[%.2s]\n", null_str),0 , "momo");
	// f_check(ft_printf("[%.1s]\n", null_str),0 , "momo");
	// f_check(printf("[%.1s]\n", null_str),0 , "momo");
	// f_check(ft_printf("[%5s\n]", "-42"),1 , "momo");
	int i1=ft_printf("[%10c]\n", '\0');
	int i2=printf("[%10c]\n", '\0');
	printf("%d %d\n",i1,i2);
	i1=ft_printf("[%5c now you see]\n", '\0');
	i2=printf("[%5c now you see]\n", '\0');
	printf("%d %d\n",i1,i2);
	
	// ft_printf("[%5s\n]", "-42");
	// ft_printf("[%01.0X]\n", 0);	
	// printf("[%01.0X]\n", 0);	
	// i1=ft_printf("[l%cl%cl%cl%cl%c]\n", '\0', '\0', '\0', 'e', '\0');
	// i2=printf("[l%cl%cl%cl%cl%c]\n", '\0', '\0', '\0', 'e', '\0');
	// printf("%d %d\n",i1,i2);
	// ft_printf("%012.11X", -1);
	// ft_printf("%012X, %20X, %2X, %000042.20X", -1, 3, 30, -1);
	// ft_printf("%012X, %X, %002X, %42.5X", -1, 3, 30, -1);
	// ft_printf("%0014.2X%020X%0002.X%000.5X", -1, 3, 30, -1);
    return 0;
}
//  125.KO (Wrong output) (Wrong return)
//         Expected: [ (null)], return: 7
//         Got:      [(null)], return: 6
//      You can rerun this test with sh test 125
//      The function was called like this:
//    ft_printf("%7s", null_str);

//   1006.KO (Wrong output) (Wrong return)
//         Expected: [ ], return: 1
//         Got:      [], return: 0
//      You can rerun this test with sh test 1006
//      The function was called like this:
//    ft_printf("%01.X", 0);

//   1007.KO (Wrong output) (Wrong return)
//         Expected: [ ], return: 1
//         Got:      [], return: 0
//      You can rerun this test with sh test 1007
//      The function was called like this:
//    ft_printf("%01.0X", 0);

//   1008.KO (Wrong output) (Wrong return)
//         Expected: [  ], return: 2
//         Got:      [], return: 0
//      You can rerun this test with sh test 1008
//      The function was called like this:
//    ft_printf("%02.0X", 0);

//   1009.KO (Wrong output) (Wrong return)
//         Expected: [   ], return: 3
//         Got:      [], return: 0
//      You can rerun this test with sh test 1009
//      The function was called like this:
//    ft_printf("%03.0X", 0);

