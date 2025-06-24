#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stdio.h>

#define FLAG_SPACE  (1 << 0)
#define FLAG_PLUS   (1 << 1)
#define FLAG_MINUS  (1 << 2)
#define FLAG_ZERO   (1 << 3)
#define FLAG_HASH   (1 << 4)
typedef enum { false, true } ft_bool;

typedef struct {
    ft_bool plus;
    ft_bool space;
    ft_bool minus;
    ft_bool zero;
    ft_bool hash;
    int width;
    int precision;
    ft_bool precision_specified;
    char specifier;
} flags_t;



int	ft_strlen(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
// char *ft_left_align(char *str, int n, char c);
// char *ft_right_align(char *str, int n, char c);
char *ft_itoa_len(int n, int *len);
char	*ft_strdup(char *s);
char *str_my_print_id(char *str, int numb);
char *str_my_print_uoxX(char *str, int numb);
char *ft_pad_string(char *str, int width, char pad_char, ft_bool left_align);
int	ft_isdigit(int c);
const char	*ft_strchr(const char *s, int c);
char	*ft_itoa_base(int n, const char *base, int *length);
char	*ft_itoa_basex(unsigned int n, const char *base, int *length);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_utoa_base_str(unsigned int n, int is_negative, const char *base,
		int *length);
char *ft_itoa_base_unsigned(unsigned int num, const char *base, int *length);
void print_float(float n, int precision);
// char *str_my_print_id(char *str, int numb) {
//     flags_t *flags = ft_find_flags_id(str);
//     char *num_str = NULL;
//     char *prec_str = NULL;
//     int len = 0;
//     const char *base = NULL;
//     char *prefix = NULL;
//     unsigned int uval = (unsigned int)numb;

//     switch (flags->specifier) {
//         case 'd':
//         case 'i':
//             base = "0123456789";
//             num_str = ft_itoa_base(numb, base, &len);
//             break;
//         case 'u':
//             base = "0123456789";
//             num_str = ft_itoa_base(uval, base, &len);
//             break;
//         case 'o':
//             base = "01234567";
//             num_str = ft_itoa_base(uval, base, &len);
//             if (flags->hash && uval != 0 && num_str[0] != '0')
//                 prefix = "0";
//             break;
//         case 'x':
//             base = "0123456789abcdef";
//             num_str = ft_itoa_base(uval, base, &len);
//             if (flags->hash && uval != 0)
//                 prefix = "0x";
//             break;
//         case 'X':
//             base = "0123456789ABCDEF";
//             num_str = ft_itoa_base(uval, base, &len);
//             if (flags->hash && uval != 0)
//                 prefix = "0X";
//             break;
//         default:
//             num_str = ft_strdup("?");
//             len = 1;
//     }

//     // Handle precision
//     if (flags->precision_specified && flags->precision > len) {
//         prec_str = ft_pad_string(num_str, flags->precision, '0', false);
//         free(num_str);
//         num_str = prec_str;
//         len = flags->precision;
//     } else if (flags->precision_specified && flags->precision == 0 && numb == 0) {
//         free(num_str);
//         num_str = ft_strdup("");
//         len = 0;
//     }

//     // Prefix (for x/X/o)
//     if (prefix) {
//         char *tmp = ft_strjoin(prefix, num_str);
//         free(num_str);
//         num_str = tmp;
//         len += ft_strlen(prefix);
//     }

//     // Width padding
//     if (flags->width > len) {
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
