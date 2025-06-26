/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:28:22 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/26 16:21:23 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_type.h"



void normalize_flags(flags_t *f) {
    if (f->plus)
        f->space = t_false;
    if (f->minus)
        f->zero = t_false;
    if (f->precision_specified && strchr("diuxX", f->specifier))
        f->zero = t_false;
    if (strchr("uxX", f->specifier)) {
        f->plus = t_false;
        f->space = t_false;
    }
    if (!strchr("xX", f->specifier))
        f->hash = t_false;
    if (strchr("csp%", f->specifier)) {
        f->plus = t_false;
        f->space = t_false;
    }
    if (f->precision_specified && !strchr("diuxXs", f->specifier)) {
        f->precision_specified = t_false;
        f->precision = 0;
    }
    if (strchr("csp", f->specifier)) {
        f->zero = t_false;
    }
}


flags_t	*ft_h_flags(flags_t *flags, const char *str)
{
	while (ft_isdigit(*str))
	{
		flags->width = flags->width * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		flags->precision_specified = t_true;
		flags->precision = 0;
		while (ft_isdigit(*str))
		{
			flags->precision = flags->precision * 10 + (*str - '0');
			str++;
		}
	}
	if (ft_strchr("diuxXoscp", *str))
		flags->specifier = *str;
	else
		flags->specifier = '-';
	normalize_flags(flags);
	return (flags);
}

flags_t *ft_find_flags_id(const char *str) {
    flags_t *flags = malloc(sizeof(flags_t));
    if (!flags)
        return NULL;
    *flags = (flags_t){0};
    if (*str == '%')
        str++;
    while (*str == '+' || *str == ' ' || *str == '-' || *str == '0' || *str == '#') {
        if (*str == '+') flags->plus = t_true;
        else if (*str == ' ') flags->space = t_true;
        else if (*str == '-') flags->minus = t_true;
        else if (*str == '0') flags->zero = t_true;
        else if (*str == '#') flags->hash = t_true;
        str++;
    }
    while (ft_isdigit(*str)) {
        flags->width = flags->width * 10 + (*str - '0');
        str++;
    }
    if (*str == '.') {
        str++;
        flags->precision_specified = t_true;
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



char *ft_get_return_str(flags_t *flags, void *value,char npp[2])
{
	char *num_str;

	num_str=NULL;

	flags->sign=0;
	if(flags->specifier=='d' || flags->specifier=='i')
	{
		num_str=ft_print_int(*(int *)value,flags->sign);
		if(*(int *)value<0)
			flags->sign=1;
	}
	if(flags->specifier=='u')
		num_str=ft_print_int(*(unsigned int *)value,flags->sign);
	if(flags->specifier=='x' || flags->specifier=='X')
	{
		npp[0] = '0';
		npp[1] = flags->specifier;
		num_str=ft_print_hex(*(unsigned int *)value,flags->specifier);
	}
	if (flags->specifier == 's')
	    num_str = (char *)value;
	else if (flags->specifier == 'c')
	{
	    num_str = malloc(2);
	    if (!num_str)
	        return NULL;
	    num_str[0] = *(char *)value;
	    num_str[1] = '\0';
	}
	else if (flags->specifier == 'p')
	{
	    npp[0]= '\0';
    	npp[1]= '\0';
		num_str = ft_print_pointer(*(void **)value);
	}
	return (num_str);
}

#include <stdlib.h>
char *str_my_print_id(char *str, int numb, void *value)
{
    flags_t *flags;


    char *num_str;
    // char *prec_str;
    int len= 0;
    char npp[2];
    npp[0]= '\0';
    npp[1]= '\0';
	flags = ft_find_flags_id(str);
	num_str=ft_get_return_str(flags, value, npp);

	len = ft_strlen(num_str);

	// Handle sign character (only for positive numbers)
	if ((flags->plus || flags->space) && num_str[0] != '-')
		npp[0] = flags->plus ? '+' : ' ';

	// Handle precision (for numbers)
	if (flags->precision_specified)
	{
		if (flags->precision == 0 && numb == 0)
		{
			free(num_str);
			num_str = ft_strdup("");
			len = 0;
		}
		else if ((flags->precision > len) && !flags->zero)
		{
			if (num_str[0] == '-')
				flags->precision++; // for '-' sign space
			num_str = ft_pad_string(num_str, flags->precision, '0', t_false);
			len = ft_strlen(num_str);
		}

	}

	// // Add '+' or ' ' if needed and no negative sign
	if (npp[0] && num_str[0] != '-')
	{
		num_str = ft_pad_string(num_str, len + 1, npp[0], t_false);
		len++;
	}

	// // Apply width padding
	// if (flags->width > len)
	// {
	// 	if (flags->minus)
	// 	{
	// 		// printf("the the looop 1");
	// 		num_str = ft_pad_string(num_str, flags->width, ' ', t_true);
	// 	}
	// 	else if (flags->zero && !flags->precision_specified)
	// 	{
	// 		// printf("the the looop 2");
	// 		if(flags->precision > len)
	// 			num_str = ft_pad_string(num_str, flags->width-1, '0', t_false);
	// 	}
	// 	else
	// 	{
	// 		// printf("the the looop 3");
	// 		num_str = ft_pad_string(num_str, flags->width, ' ', t_false);
	// 	}
	// }
	// len=ft_strlen(num_str);
	if (flags->width > len)
	{
		if (!flags->minus && flags->zero)
		{
			char *temp;
			if(flags->sign==1 || num_str[0] != '-')
				temp = ft_pad_string(num_str, len+1, '-', t_false);
			free(num_str);
			num_str = ft_pad_string(temp, flags->width, '0', t_false);
			free(temp);
		}
		if (!flags->minus && !flags->zero)
			num_str = ft_pad_string(num_str, flags->width, ' ', t_false);
		if (!flags->minus && flags->zero)
			num_str = ft_pad_string(num_str, flags->width, '0', t_false);
		else if (flags->zero && !flags->precision_specified)
		{
			// printf("the the looop 2");
			if(flags->precision > len)
				num_str = ft_pad_string(num_str, flags->width-1, '0', t_false);
		}
		// else
		// {
		// 	// printf("the the looop 3");
		// 	num_str = ft_pad_string(num_str, flags->width, ' ', t_false);
		// }
	}
	// if(!flags->precision_specified)
	if(flags->sign==1 || num_str[0] == '-')
		num_str = ft_pad_string(num_str, len+1, '-', t_false);
    free(flags);
    return num_str;
}





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
