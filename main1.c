#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    bool plus;
    bool space;
    bool minus;
    bool zero;
    bool hash;
    bool precision_specified;
    int width;
    int precision;
    char specifier;
} flags_t;

int ft_isdigit(char c) {
    return c >= '0' && c <= '9';
}

char *ft_strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c) return (char *)s;
        s++;
    }
    return NULL;
}

// --- From previous definition ---
void normalize_flags(flags_t *f) {
    if (f->plus)
        f->space = false;
    if (f->minus)
        f->zero = false;
    if (f->precision_specified && strchr("diuxX", f->specifier))
        f->zero = false;
    if (strchr("uxX", f->specifier)) {
        f->plus = false;
        f->space = false;
    }
    if (!strchr("xX", f->specifier))
        f->hash = false;
    if (strchr("csp%", f->specifier)) {
        f->plus = false;
        f->space = false;
    }
    if (f->precision_specified && !strchr("diuxXs", f->specifier)) {
        f->precision_specified = false;
        f->precision = 0;
    }
    if (strchr("csp", f->specifier)) {
        f->zero = false;
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
    if (ft_strchr("diuxXcsp%", *str))
        flags->specifier = *str;
    else
        flags->specifier = 0;

    normalize_flags(flags);
    return flags;
}

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
void ft_flag_c(flags_t *f) {
    if (f->minus)
        printf("left-justify ");
    else
        printf("right-justify ");
    if (f->width)
        printf("width=%d ", f->width);
}

void ft_flag_s(flags_t *f) {
    if (f->minus)
        printf("left-justify ");
    else
        printf("right-justify ");
    if (f->width)
        printf("width=%d ", f->width);
    if (f->precision_specified)
        printf("precision=%d ", f->precision);
}

void ft_flag_p(flags_t *f) {
    if (f->minus)
        printf("left-justify ");
    else
        printf("right-justify ");
    if (f->width)
        printf("width=%d ", f->width);
    printf("pointer-prefix ");
}

// void ft_flag_id(flags_t *f) {
//     if (f->minus)
//         printf("left-justify ");
//     else
//         printf("right-justify ");
//     if (f->width)
//         printf("width=%d ", f->width);
//     if (f->plus)
//         printf("show-sign ");
//     else if (f->space)
//         printf("space-sign ");
//     if (f->zero)
//         printf("zero-pad ");
//     if (f->precision_specified)
//         printf("precision=%d ", f->precision);
// }



void ft_flag_id(flags_t *f, int value) {
    char num_buf[32];
    int abs_val = value < 0 ? -value : value;
    int is_negative = value < 0;

    // Convert integer to string (manual or sprintf-based)
    snprintf(num_buf, sizeof(num_buf), "%d", abs_val);
    int digit_len = strlen(num_buf);

    // Apply precision: leading zeros
    int prec_zeros = 0;
    if (f->precision_specified && f->precision > digit_len)
        prec_zeros = f->precision - digit_len;

    // Determine sign char
    char sign = 0;
    if (is_negative) sign = '-';
    else if (f->plus) sign = '+';
    else if (f->space) sign = ' ';

    // Total formatted length before width padding
    int len = digit_len + prec_zeros + (sign ? 1 : 0);

    // Apply width: padding spaces or zeros (if allowed)
    int pad = 0;
    char pad_char = ' ';
    if (f->width > len) {
        pad = f->width - len;
        if (f->zero && !f->precision_specified && !f->minus)
            pad_char = '0';
    }

    // --- Print final result ---
    if (!f->minus && pad_char == ' ') while (pad--) putchar(' '); // left padding

    if (sign) putchar(sign);

    if (!f->minus && pad_char == '0') while (pad--) putchar('0'); // left zero padding

    while (prec_zeros--) putchar('0');
    fputs(num_buf, stdout);

    if (f->minus) while (pad--) putchar(' '); // right padding
}

void ft_flag_u(flags_t *f) {
    if (f->minus)
        printf("left-justify ");
    else
        printf("right-justify ");
    if (f->width)
        printf("width=%d ", f->width);
    if (f->zero)
        printf("zero-pad ");
    if (f->precision_specified)
        printf("precision=%d ", f->precision);
}

void ft_flag_xX(flags_t *f) {
    if (f->minus)
        printf("left-justify ");
    else
        printf("right-justify ");
    if (f->width)
        printf("width=%d ", f->width);
    if (f->hash)
        printf("prefix-0x ");
    if (f->zero)
        printf("zero-pad ");
    if (f->precision_specified)
        printf("precision=%d ", f->precision);
}

void ft_flag_percent(flags_t *f) {
    if (f->minus)
        printf("left-justify ");
    else
        printf("right-justify ");
    if (f->width)
        printf("width=%d ", f->width);
    if (f->zero)
        printf("zero-pad ");
}
void print_flags(const char *format, flags_t *f) {
    if (f->specifier == 0) {
        printf("Format: %-10s → Invalid specifier\n", format);
        return;
    }

    printf("Format: %-10s → ", format);
    printf("specifier='%c', ", f->specifier);
    printf("plus=%d, space=%d, minus=%d, zero=%d, hash=%d, width=%d, ",
           f->plus, f->space, f->minus, f->zero, f->hash, f->width);
    if (f->precision_specified)
        printf("precision=%d\n", f->precision);
    else
        printf("precision=NA\n");

    printf("  [Effective flags]: ");
    if (f->specifier == 'c')
        ft_flag_c(f);
    else if (f->specifier == 's')
        ft_flag_s(f);
    else if (f->specifier == 'p')
        ft_flag_p(f);
    else if (f->specifier == 'd' || f->specifier == 'i')
        ft_flag_id(f, 24);
    else if (f->specifier == 'u')
        ft_flag_u(f);
    else if (f->specifier == 'x' || f->specifier == 'X')
        ft_flag_xX(f);
    else if (f->specifier == '%')
        ft_flag_percent(f);
    else
        printf("unknown-specifier ");
    printf("\n");
}

int main(void) {
    const char *test_formats[] = {
        "%05d", "%-10s", "%+6d", "% 6d", "%#08x", "%#x", "%.5d", "%06.3d",
        "%+05d", "%-#10x", "%#-10x", "%05s", "%#d", "%+u", "%p", "%-5%", NULL
    };

    // for (int i = 0; test_formats[i]; i++) {
    //     flags_t *f = ft_find_flags_id(test_formats[i]);
    //     if (f) {
    //         print_flags(test_formats[i], f);
    //         free(f);
    //     } else {
    //         printf("Failed to parse: %s\n", test_formats[i]);
    //     }
    // }
    flags_t f = {
        .plus = 1,
        .zero = 1,
        .width = 8,
        .precision_specified = 1,
        .precision = 5,
        .specifier = 'd'
    };
    ft_flag_id(&f, -42);

    return 0;
}
