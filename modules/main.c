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
// char *capture_my_printf(const char *format, ...)
// {
//     int pipefd[2];
//     va_list args;
//     char *buf = malloc(1024);
//     if (!buf) return NULL;

//     fflush(stdout);
//     pipe(pipefd);
//     int stdout_copy = dup(STDOUT_FILENO);
//     dup2(pipefd[1], STDOUT_FILENO);
//     close(pipefd[1]);

//     va_start(args, format);
//     int value = va_arg(args, int);
//     str_my_print_id((char *)format, value);
//     va_end(args);

//     fflush(stdout);
//     read(pipefd[0], buf, 1023);
//     close(pipefd[0]);
//     dup2(stdout_copy, STDOUT_FILENO);
//     close(stdout_copy);

//     buf[1023] = '\0'; // ensure null-terminated
//     return buf;
// }
// void run_test(const char *desc, const char *format, int value)
// {
//     char expected[1024];
//     snprintf(expected, sizeof(expected), format, value); // expected output from standard printf

//     char *out = str_my_print_id((char *)format, value);
//     if (!out) {
//         printf(RED "%s: FAIL (NULL output)" RESET "\n", desc);
//         return;
//     }


//     int ok = strcmp(out, expected) == 0;

//     // printf("%s: ", desc);
//     if (ok)
//         printf(GREEN " OK " RESET );
//     else {
//         printf(RED " KO " RESET);
//         printf(RED "FAIL" RESET "\n");
//         printf("  Format  : \"%s\"\n", format);
//         printf("  Value   : %d\n", value);
//         printf("  Expected: \"%s\"\n", expected);
//         printf("  Got     : \"%s\"\n", out);
//     }

//     free(out); // Important: free the memory returned by str_my_print_id
// }



// int main(void)
// {

//     printf("\n");
//     run_test("Unsigned basic", "%u", 12345);
//     run_test("Octal basic", "%o", 64);             // "100"
//     run_test("Octal with #", "%#o", 64);           // "0100"
//     run_test("Hex lower", "%x", 255);              // "ff"
//     run_test("Hex upper", "%X", 255);              // "FF"
//     run_test("Hex with #", "%#x", 255);            // "0xff"
//     run_test("Hex with # and upper", "%#X", 255);  // "0XFF"
//     run_test("Hex width", "%8x", 255);             // "     ff"
//     run_test("Hex zero padded", "%08x", 255);      // "000000ff"
//     run_test("Hex width + #", "%#8x", 255);        // "   0xff"
//     run_test("Octal + precision", "%.5o", 10);     // "00012"
//     run_test("Octal zero with #", "%#o", 0);        // expect "0"
//     run_test("Hex zero with #", "%#x", 0);          // expect "0"
//     run_test("Hex upper zero with #", "%#X", 0);    // expect "0"
//     run_test("Unsigned max", "%u", UINT_MAX);
//     run_test("Hex max", "%x", UINT_MAX);
//     run_test("Octal max", "%o", UINT_MAX);
//     run_test("Precision 0 zero unsigned", "%.0u", 0); // expect ""
//     run_test("Precision 0 zero octal", "%.0o", 0);    // expect ""
//     run_test("Zero pad with precision and # octal", "%#08.5o", 64);  // expect "00000100" (no extra 0 prefix)
//     run_test("Zero pad with precision and # hex", "%#010.5x", 255);  // expect "     000ff" or "0x000ff" depending on spec
//     run_test("Width smaller than prefix+num", "%#3x", 15);  // expect "0xf"
//     run_test("Left justify with # octal", "%-#6o", 10);  // expect "012   "
//     run_test("Left justify with # hex", "%-#6x", 10);    // expect "0xa   "
//     run_test("Negative input unsigned", "%u", -1);  // expect UINT_MAX
//     run_test("Negative input hex", "%x", -1);       // expect "ffffffff" (or 64-bit equivalent)

//     printf("\n");
//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// // Your integer to ASCII converter, returns malloc'd string
// // You can replace this with your own implementation.
// char *ft_itoa_len(long n, int *len) {
//     int negative = 0;
//     long num = n;
//     int digits = 0;
//     if (num == 0) digits = 1;
//     if (num < 0) {
//         negative = 1;
//         num = -num;
//     }
//     long temp = num;
//     while (temp > 0) {
//         temp /= 10;
//         digits++;
//     }
//     *len = digits + negative;
//     char *str = malloc(*len + 1);
//     if (!str) return NULL;
//     str[*len] = '\0';

//     if (negative) str[0] = '-';
//     if (num == 0) {
//         str[0] = '0';
//         return str;
//     }

//     for (int i = *len - 1; i >= negative; i--) {
//         str[i] = (num % 10) + '0';
//         num /= 10;
//     }
//     return str;
// }

#include <stdio.h>
#include <stdlib.h>

// void split_float(float n, int precision, long *int_part, long *dec_part)
// {
//     float frac_part;
//     long power;
//     int i;

//     *int_part = (long)n;
//     frac_part = n - (float)(*int_part);
//     if (frac_part < 0) frac_part = -frac_part;
//     power = 1;
//     i = 0;
//     while (i < precision) {
//         power *= 10;
//         i++;
//     }
//     *dec_part = (long)(frac_part * power + 0.5f);
// }

// int main() {
//     float numbers[] = {123.4567f, -123.4567f, 0.00123f, -0.00123f, 100.0f};
//     int precision = 6;
//     int count = sizeof(numbers) / sizeof(numbers[0]);

//     for (int i = 0; i < count; i++) {
//         long int_part, dec_part;
//         split_float(numbers[i], precision, &int_part, &dec_part);

//         printf("Number: %f\n", numbers[i]);
//         printf("Integer part: %ld\n", int_part);
//         printf("Decimal part (scaled): %0*ld\n\n", precision, dec_part);
//     }

//     return 0;
// }


// int main() {
//     print_float(123.4567f, 4);
//     print_float(-0.00987f, 5);
//     print_float(-123.0f, 3);
//     print_float(0.0f, 2);
//     return 0;
// }

#include <stdio.h>

#include <stdlib.h>
#include <math.h>

typedef struct {
    float numb;
    int sign;
    long inpart;
    int intleng;
    int expint;
    int expdec;
    char *exp;
    char *inststr;
    long decpart;
    int decleng;
    int procision;
    int tlen;
    char *decstr;
    char *floatstr;
} My_float;


// static void construct_to_ind(My_float *to_pout) {
//     int i;
//     int j;

//     if (to_pout->sign)
//         to_pout->floatstr[0] = '-';
//     i = to_pout->sign;
//     j = 0;
//     while (j < to_pout->intleng) {
//         to_pout->floatstr[i + j] = to_pout->inststr[j];
//         j++;
//     }
//     to_pout->floatstr[i + j] = '.';
//     i = i + j + 1;
//     j = 0;
//     while (j < to_pout->decleng) {
//         to_pout->floatstr[i + j] = to_pout->decstr[j];
//         j++;
//     }
//     to_pout->floatstr[i + j] = '\0';
// }


void ft_get_positions(My_float *to_pout)
{
    int i;
    int len;

    i=0;
    while (i<to_pout->intleng)
    {
        if(to_pout->inststr[i]!='0' && to_pout->inststr[i]!='+' && to_pout->inststr[i]!='-')
        {
            to_pout->expint=to_pout->intleng-i;
            to_pout->exp=ft_itoa_len(to_pout->intleng-i,&len);
            break;
        }
        i++;
    }
    i=0;
    while (i<to_pout->decleng && to_pout->expint != -1)
    {
        if(to_pout->decstr[i]!='0' && to_pout->decstr[i]!='+' && to_pout->decstr[i]!='-')
        {
            to_pout->expint=i+1;
            to_pout->exp=ft_itoa_len(i+1,&len);
            break;
        }
        i++;
    }
}


static void construct_to_exp_ind(My_float *to_pout)
{
    int i, j;
    char *new;


    to_pout->expint =-1;
    to_pout->expdec =-1;
    ft_get_positions(to_pout);
    to_pout->exp=ft_pad_string(to_pout->exp, 2,'0',false);
    if(to_pout->expint !=-1)
        to_pout->exp=ft_pad_string(to_pout->exp, 3,'+',false);
    else
        to_pout->exp=ft_pad_string(to_pout->exp, 3,'-',false);
    to_pout->exp=ft_pad_string(to_pout->exp, 4,'e',false);

    int len = to_pout->sign + to_pout->intleng + 1 + to_pout->procision + 4 + 1+2; // sign + digit + dot + decimals + exp (e±XX) + \0

    new = malloc(len * sizeof(char));
    if (!new)
        return;
    i = 0;
    if (to_pout->sign)
        new[i++] = '-';
    j=0;
    int found =-1;
    while (j<to_pout->intleng)
    {
        new[i++] = to_pout->inststr[j];
        if(to_pout->inststr[j]!='0' && to_pout->inststr[j]!='+' && to_pout->inststr[j]!='-' && found !=-2)
        {
            found=-2;
            new[i++] = '.';
        }  
        j++;
    }
    
    j=0;
    while (j<to_pout->decleng)
    {
        new[i++] = to_pout->decstr[j];
        if(to_pout->decstr[j]!='0' && to_pout->decstr[j]!='+' && to_pout->decstr[j]!='-' && found ==-1)
        {
            found=-2;
            new[i++] = '.';
        }
        j++;
    }
    j=0;
    while (j<4)
         new[i++] = to_pout->exp[j++];
    
    new[i] = '\0';
    to_pout->floatstr=new;
    
    // free(new);
}

static void convert_to_ind(My_float *to_pout) {
    int i;
    int pow;

    i = 0;
    pow = 1;
    while (i++ < to_pout->procision)
        pow *= 10;
    to_pout->decpart = (long)(pow * (to_pout->numb - (float)to_pout->inpart) + 0.5f);
    to_pout->inststr = ft_itoa_len(to_pout->inpart, &to_pout->intleng);
    to_pout->decstr = ft_itoa_len(to_pout->decpart, &to_pout->decleng);
    to_pout->decstr = ft_pad_string(to_pout->decstr, to_pout->procision, '0', false);
    to_pout->decleng = to_pout->procision;
    to_pout->tlen = to_pout->tlen + to_pout->intleng + to_pout->decleng + 5;
    // to_pout->floatstr = malloc((to_pout->tlen + 5) * sizeof(char));
    // if (!to_pout->floatstr)
    //     return;
    // construct_to_ind(to_pout);
    construct_to_exp_ind(to_pout);
    printf("the str new is ->> %s\n", to_pout->floatstr);
}

char *ft_simple_rtstr(My_float *to_pout)
{
    char *result;
    int i;

    result = malloc((to_pout->tlen +2) * sizeof(char));
    if (!result) {
        free(to_pout->inststr);
        free(to_pout->decstr);
        free(to_pout->floatstr);
        free(to_pout->exp);
        free(to_pout);
        return NULL;
    }
    i = 0;
    while (i < to_pout->tlen + 1) {
        result[i] = to_pout->floatstr[i];
        i++;
    }
    result[i] = '\0';
    free(to_pout->inststr);
    free(to_pout->decstr);
    free(to_pout->floatstr);
    free(to_pout->exp);
    free(to_pout);
    return (result);
}



char *My_float_to_string(float numb) {
    My_float *to_pout;

    if (isnan(numb))
        return ft_strdup("nan");
    if (isinf(numb))
        return ft_strdup(numb < 0 ? "-inf" : "inf");
    to_pout = malloc(sizeof(My_float));
    if (!to_pout)
        return NULL;
    to_pout->sign = 0;
    to_pout->tlen = 0;
    to_pout->procision = 6;
    if (numb < 0) {
        numb = -numb;
        to_pout->sign = 1;
        to_pout->tlen = 1;
    }
    to_pout->numb = numb;
    to_pout->inpart = (long)numb;

    convert_to_ind(to_pout);
    // if (!to_pout->floatstr) {
    //     free(to_pout);
    //     return NULL;
    // }
    // return (ft_simple_rtstr(to_pout));
    return ("momo");
}
int main() {
    char *str;
    // Example test numbers
    float testNumbers[] = {123.456f, -78.0091011f, 0.12345f, -0.98765f, 1000.0f};
    // float testNumbers[] = {-123.456f, 78.0091011f, 0.12345f, 0.98765f, 1000.0f};
    int size = sizeof(testNumbers) / sizeof(testNumbers[0]);

    for (int i = 0; i < size; i++) {

        float num = testNumbers[i];
        printf("%.6f\n",num);
        // str=My_float_to_string(num);
        // str=ft_build_strfloat_simple(num);
        printf("%s\n",str);
        // free(str);
    }

    return 0;
}
