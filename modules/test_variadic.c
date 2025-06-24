#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include "libft.h"


void normalize_flags(flags_t *f) {
    if (f->plus)
        f->space = false;
    if (f->minus)
        f->zero = false;
    if (f->precision_specified)
        f->zero = false;
    if (f->specifier=='-')
    {
        f->plus = false;
        f->space = false;
    }
}

flags_t *ft_find_flags_id(const char *str) {
    flags_t *flags = malloc(sizeof(flags_t));
    if (!flags)
        return NULL;
    *flags = (flags_t){0};
    if (*str == '%')
        str++;
    while (*str == '+' || *str == ' ' || *str == '-' || *str == '0' || *str == '#') {
        if (*str == '+') flags->plus = true;
        else if (*str == ' ') flags->space = true;
        else if (*str == '-') flags->minus = true;
        else if (*str == '0') flags->zero = true;
        else if (*str == '#') flags->hash = true;
        str++;
    }
    while (ft_isdigit(*str)) {
        flags->width = flags->width * 10 + (*str - '0');
        str++;
    }
    if (*str == '.') {
        str++;
        flags->precision_specified = true;
        flags->precision = 0;
        while (ft_isdigit(*str)) {
            flags->precision = flags->precision * 10 + (*str - '0');
            str++;
        }
    }
    if (ft_strchr("diuxXoscp", *str))
        flags->specifier = *str;
    else
       flags->specifier = '-'; 
    normalize_flags(flags);
    return flags;
}


char *str_my_print_id(char *str, int numb) {
    flags_t *flags = ft_find_flags_id(str);
   

    char *num_str;
    char *prec_str;
    int len= 0;
    char npp[2];
    // char prefix = '\0';
    const char *base = NULL;
    unsigned int uval = (unsigned int)numb;
    // char *prefix = NULL;
    // const char *bin = "01";
    // const char *oct = "01234567";
    // const char *dec = "0123456789";
    // const char *hex_l = "0123456789abcdef";
    // const char *hex_u = "0123456789ABCDEF";
    npp[0]= '\0';
    npp[1]= '\0';
    switch (flags->specifier)
    {
        case 'd':
        case 'i':
            base = "0123456789";
            num_str = ft_itoa_base(numb, base, &len);
            // free(base);
            break;
        case 'u':
            base = "0123456789";
            num_str = ft_itoa_base(uval, base, &len);
            break;
        case 'o':
            base = "01234567";
            num_str = ft_itoa_base(uval, base, &len);
            if (flags->hash && uval != 0 && num_str[0] != '0')
                npp[0] = '0';
            break;
        case 'x':
            base = "0123456789abcdef";
            num_str = ft_itoa_base(uval, base, &len);
            if (flags->hash && uval != 0)
            {
                npp[0] = '0';
                npp[1] = 'x';
            }
            break;
        case 'X':
            base = "0123456789ABCDEF";
            num_str = ft_itoa_base(uval, base, &len);
            if (flags->hash && uval != 0)
            {
                npp[0] = '0';
                npp[1] = 'X';
            }
            break;
        default:
            num_str = ft_strdup("?");
            len = 1;


    }

 
    // Step 2: Prefix
    if (numb < 0) npp[0] = '-';
    else if (flags->plus) npp[0] = '+';
    else if (flags->space) npp[0] = ' ';

    // Step 3: Precision (pad with '0's)
    

    
    if (flags->precision_specified && flags->precision > len) {
        if(num_str[0]=='-')
            flags->precision++;
        prec_str = ft_pad_string(num_str, flags->precision, '0',false);
        // free(num_str);
        num_str = prec_str;
        len = flags->precision;
    } else if (flags->precision_specified && flags->precision == 0 && numb == 0) {
        free(num_str);
        num_str = ft_strdup("");
        len = 0;
    }
    if (npp[0] && num_str[0]!='-') {
        num_str=ft_pad_string(num_str, len + 1, npp[0],false);
        len++;
    }
    if (flags->width > len) {
        if (flags->minus) {
            num_str = ft_pad_string(num_str, flags->width, ' ',true);
        } else if (flags->zero && !flags->precision_specified) {
            num_str = ft_pad_string(num_str, flags->width, '0',false);
        } else {
            num_str = ft_pad_string(num_str, flags->width, ' ',false);
        }
    }
    free(flags);
    return num_str;
}









// char *str_my_print_uoxX(char *str, int numb) {
//     flags_t *flags = ft_find_flags_id(str);

//     char *num_str;
//     char *prec_str;
//     int len = 0;
//     const char *base = NULL;
//     unsigned int uval = (unsigned int)numb;

//     switch (flags->specifier)
//     {
//         case 'u':
//             base = "0123456789";
//             num_str = ft_itoa_base_unsigned(uval, base, &len);
//             break;
//         case 'o':
//             base = "01234567";
//             num_str = ft_itoa_base_unsigned(uval, base, &len);
//             break;
//         case 'x':
//             base = "0123456789abcdef";
//             num_str = ft_itoa_base_unsigned(uval, base, &len);
//             break;
//         case 'X':
//             base = "0123456789ABCDEF";
//             num_str = ft_itoa_base_unsigned(uval, base, &len);
//             break;
//         default:
//             num_str = ft_strdup("?");
//             len = 1;
//     }

//     // Handle precision
//     if (flags->precision_specified && flags->precision > len) {
//         prec_str = ft_pad_string(num_str, flags->precision, '0', false);
//         num_str = prec_str;
//         len = flags->precision;
//     } else if (flags->precision_specified && flags->precision == 0 && uval == 0) {
//         free(num_str);
//         num_str = ft_strdup("");
//         len = 0;
//     }

//     // Handle prefix
//     char prefix[3] = {'\0'};
//     int prefix_len = 0;
//     if (flags->specifier == 'o' && flags->hash && num_str[0] != '0') {
//         prefix[prefix_len++] = '0';
//     } else if ((flags->specifier == 'x' || flags->specifier == 'X') && flags->hash && uval != 0) {
//         prefix[prefix_len++] = '0';
//         prefix[prefix_len++] = (flags->specifier == 'x') ? 'x' : 'X';
//     }
//     prefix[prefix_len] = '\0';

//     // Prepend prefix if needed
//     if (prefix_len > 0) {
//         char *tmp = malloc(prefix_len + strlen(num_str) + 1);
//         strcpy(tmp, prefix);
//         strcat(tmp, num_str);
//         free(num_str);
//         num_str = tmp;
//         len += prefix_len;
//     }

//     // Handle width
//     if (flags->width > len) {
//         if (flags->minus) {
//             num_str = ft_pad_string(num_str, flags->width, ' ', true);
//         } else if (flags->zero && !flags->precision_specified) {
//             num_str = ft_pad_string(num_str, flags->width, '0', false);
//         } else {
//             num_str = ft_pad_string(num_str, flags->width, ' ', false);
//         }
//     }

//     free(flags);
//     return num_str;
// }





// char *str_my_print_efgGaA(char *str, double val)
// {
//     flags_t *flags = ft_find_flags_id(str);
//     char *num_str = NULL;
//     char *prefix = NULL;
//     int precision = flags->precision_specified ? flags->precision : 6;

//     // Determine the format specifier
//     switch (flags->specifier)
//     {
//         case 'f':
//         case 'F':
//             num_str = ft_dtoa_fixed(val, precision); // You need to implement this
//             break;
//         case 'e':
//         case 'E':
//             num_str = ft_dtoa_exponential(val, precision, flags->specifier == 'E'); // Implement
//             break;
//         case 'g':
//         case 'G':
//             num_str = ft_dtoa_general(val, precision, flags->specifier == 'G'); // Optional, can use e/f fallback
//             break;
//         case 'a':
//         case 'A':
//             num_str = ft_dtoa_hex(val, precision, flags->specifier == 'A'); // Optional hex float format
//             break;
//         default:
//             num_str = ft_strdup("?");
//     }

//     // Optional '+' or ' ' prefix for positive numbers
//     if (val >= 0.0)
//     {
//         if (flags->plus)
//             prefix = ft_strdup("+");
//         else if (flags->space)
//             prefix = ft_strdup(" ");
//     }
//     else
//     {
//         prefix = ft_strdup(""); // Already has '-' in num_str
//     }

//     if (prefix)
//     {
//         char *tmp = malloc(strlen(prefix) + strlen(num_str) + 1);
//         strcpy(tmp, prefix);
//         strcat(tmp, num_str);
//         free(num_str);
//         free(prefix);
//         num_str = tmp;
//     }

//     // Handle width and padding
//     int len = strlen(num_str);
//     if (flags->width > len)
//     {
//         if (flags->minus)
//             num_str = ft_pad_string(num_str, flags->width, ' ', true);
//         else if (flags->zero && !flags->precision_specified)
//             num_str = ft_pad_string(num_str, flags->width, '0', false);
//         else
//             num_str = ft_pad_string(num_str, flags->width, ' ', false);
//     }

//     free(flags);
//     return num_str;
// }
