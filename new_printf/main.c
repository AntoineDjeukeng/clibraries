#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <float.h>
#include <math.h>

#include "libft.h" // Replace with your actual header file name


void print_number_type(t_number_type *n)
{
    printf("intpar : %s\n", n->intpar ? n->intpar : "(null)");
    if (n->decpart)
        printf("decpart: %s\n", n->decpart);
    else
        printf("decpart: (null)\n");

    printf("intlen : %d\n", n->intlen);
    printf("declen : %d\n", n->declen);
}

char *ft_print_float(float nub, int precision)
{
    t_number_type *number;
    char *result;
    char *str;
    int len, i, j;

    number = ft_itoa_float_split(nub, precision);
    if (!number || !number->intpar)
        return (NULL);

    len = number->intlen;
    if (number->decpart)
        len += 1 + precision;  // +1 for the decimal point

    result = malloc(len + 1);  // +1 for '\0'
    if (!result)
    {
        free(number->intpar);
        if (number->decpart)
            free(number->decpart);
        free(number);
        return (NULL);
    }

    // Copy intpart
    for (i = 0; i < number->intlen; ++i)
        result[i] = number->intpar[i];

    // Copy decimal point and decpart if it exists
    if (number->decpart)
    {
        str= ft_pad_string(number->decpart,precision,'0',false);
        result[i++] = '.';
        for (j = 0; j < precision; ++j)
            result[i++] = str[j];
    }

    result[i] = '\0';

    free(number->intpar);
    if (str)
        free(str);
    free(number);

    return result;
}





// int main(void)
// {
//     t_number_type *n;


//     n = ft_itoa_int_split(-12345);
//     printf("int -12345\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_long_split(987654321L);
//     printf("long 987654321\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_long_long_split(-9223372036854775807LL);
//     printf("long long -9223372036854775807\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_short_split((short)-32768);
//     printf("short -32768\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_char_split((char)-42);
//     printf("char -42\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_uint_split(4294967295U);
//     printf("unsigned int 4294967295\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_ulong_split(18446744073709551615UL);
//     printf("unsigned long 18446744073709551615\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_ullong_split(18446744073709551615ULL);
//     printf("unsigned long long 18446744073709551615\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_ushort_split((unsigned short)65535);
//     printf("unsigned short 65535\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_uchar_split((unsigned char)255);
//     printf("unsigned char 255\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n);

//     n = ft_itoa_float_split(-3.14159f, 5);
//     printf("float -3.14159\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n->decpart);
//     free(n);

//     n = ft_itoa_double_split(2.718281828, 8);
//     printf("double 2.718281828\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n->decpart);
//     free(n);

//     n = ft_itoa_long_double_split(1.618033988749894L, 10);
//     printf("long double 1.618033988749894\n");
//     print_number_type(n);
//     free(n->intpar);
//     free(n->decpart);
//     free(n);

//     return 0;
// }






#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

// Helper to compare float output
void run_float_test(const char *desc, float value, int precision) {
    char format[16];
    char expected[128];

    snprintf(format, sizeof(format), "%%.%df", precision);
    snprintf(expected, sizeof(expected), format, value);

    char *got = ft_print_float(value, precision);
    if (!got) {
        printf(RED "%s: FAIL (NULL output)\n" RESET, desc);
        return;
    }

    if (strcmp(got, expected) == 0)
        printf(GREEN " OK  " RESET "%s\n", desc);
    else {
        printf(RED "FAIL" RESET " %s\n", desc);
        printf("  Expected: \"%s\"\n", expected);
        printf("  Got     : \"%s\"\n", got);
    }

    free(got);
}

int main(void) {
    run_float_test("Zero", 0.0f, 6);
    run_float_test("One", 1.0f, 6);
    run_float_test("Pi", 3.141592f, 6);
    run_float_test("Negative Pi", -3.141592f, 6);
    run_float_test("Big number", 123456.789f, 3);
    run_float_test("Small number", 0.000123f, 6);
    run_float_test("Negative small", -0.000123f, 6);
    run_float_test("Very small (subnormal)", 1e-38f, 8);
    run_float_test("FLT_MAX", FLT_MAX, 2);
    run_float_test("FLT_MIN", FLT_MIN, 6);
    run_float_test("FLT_EPSILON", FLT_EPSILON, 10);
    run_float_test("Rounding", 1.999999f, 5);
    run_float_test("Half rounding", 1.55555f, 3);

    printf("\n");
    return 0;
}
