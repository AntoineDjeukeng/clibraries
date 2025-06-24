/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:22:11 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/13 13:25:06 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct t_snumb
{
	int		sign;      // 0 = positive, 1 = negative
	int		exponent;  // scientific exponent
	long		whole;     // whole part of mantissa (before decimal)
	int		fraction;  // fractional part of mantissa, scaled
	int		precision; // number of digits in fraction
    int     type;
}			t_snumb;

typedef enum { false, true } ft_bool;



int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

int	count_digits(int n)
{
	int	len;
	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total;
	void			*ptr;
	unsigned char	*p;
	size_t			i;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	p = (unsigned char *)ptr;
	i = 0;
	while (i < total)
	{
		p[i] = 0;
		i++;
	}
	return (ptr);
}


static int pad_negative_with_zeros(char *str, char *result, int padding)
{
    int i;
    int j;
    
    i = 0;
    j = 1;
    if (str[0] == '-')
        result[i++] = '-';
    if (str[0] == '+')
        result[i++] = '+';
    while (i < padding + 1)
        result[i++] = '0';
    while (str[j])
        result[i++] = str[j++];
    return i;
}


static char *ft_right_align(char *str, int n, char c)
{
    int length;
    int i;
    int j;
    char *result;
    int padding;

    length = ft_strlen(str);
    result = ft_calloc(n + 1, sizeof(char));
    if (!result)
        return NULL;
    if (n < length)
        n = length;
    padding = n - length;
    i = 0;
    j = 0;
    if ((str[0] == '-' || str[0] == '+') && c == '0')
        i = pad_negative_with_zeros(str, result, padding);
    else
    {
        while (i < padding)
            result[i++] = c;
        while (i < n && str[j])
            result[i++] = str[j++];
    }
    result[n] = '\0';
    free(str);
    return result;
}


static char *ft_left_align(char *str, int n, char c)
{
    int length ;
    char *result;
    int i ;

    length = ft_strlen(str);
    result = ft_calloc(n + 1, sizeof(char));
    i = 0;
    if (!result)
        return NULL;
    while (i < length && i < n)
    {
        result[i] = str[i];
        i++;
    }
    while (i < n)
    {
        result[i] = c;
        i++;
    }
    result[n] = '\0';
    free(str);
    return result;
}

/**
 * ft_pad_string - pads a string to a given width, either left- or right-aligned.
 * @str: The original string to pad. This string is freed inside the called function.
 * @width: The total width of the resulting padded string.
 * @pad_char: The character used to pad the string.
 * @left_align: If true, pads on the right (left-aligns the string);
 *              if false, pads on the left (right-aligns the string).
 *
 * Returns: A newly allocated string of length @width with the original string 
 *          padded and aligned according to @left_align.
 *          If allocation fails, returns NULL.
 *
 * Example:
 *     ft_pad_string(ft_strdup("Hi"), 5, '.', false) → "...Hi"
 *     ft_pad_string(ft_strdup("Hi"), 5, '.', true)  → "Hi..."
 */
char *ft_pad_string(char *str, int width, char pad_char, ft_bool left_align)
{
    if(left_align)
        return (ft_left_align(str, width, pad_char));
    else
        return (ft_right_align(str, width, pad_char));
}


char *ft_itoa_len(int n, int *len)
{
	char	*str;
	long	num;
	int 	lent;

	lent = count_digits(n);
	*len = lent;
	str = malloc(lent + 1);
	num = n;
	if (!str)
		return (NULL);
	str[lent] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		if(!(int)(-num) && (int)(-num -1))
			num++;
		num = -num;
	}
	else if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--lent] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

static void ft_get_factpart(t_snumb *result, double mantissa)
{
	int		pow10;
	int		i;
	double	frac_part;

	pow10 = 1;
	i = 0;
	result->whole = (int)mantissa;
	frac_part = mantissa - result->whole;
	while (i++ < result->precision)
		pow10 *= 10;
	result->fraction = (int)(frac_part * pow10 + 0.5);
}

static void	ft_hand_snumb(t_snumb *result, double numb)
{
	int		exponent;
    
	exponent = 0;
    
	while (numb >= 10.0 && result->type==1)
	{
		numb /= 10.0;
		exponent++;
	}
	while (numb < 1.0 && result->type==1)
	{
		numb *= 10.0;
		exponent--;
	}
	ft_get_factpart(result, numb);
	result->exponent = exponent;
}
#include <math.h>
#include <float.h>

t_snumb	*ft_convert_to_s_number(double numb, int precision, int type)
{
	t_snumb	*result;

	result = malloc(sizeof(t_snumb));
	if (!result)
		return (NULL);

	result->sign = (numb < 0);
	if (numb < 0)
		numb = -numb;
	result->precision = precision;
    result->type = type;
	if ( numb<FLT_MIN || numb == 0.0)
	{
		result->whole = 0;
		result->fraction = 0;
		result->exponent = 0;
		return (result);
	}
	ft_hand_snumb(result, numb);

	return (result);
}
void ft_handle_exponent(char *str, int exponent)
{
    int len;
    char *temp;
    int i = 0, j = 0;

    if (exponent < 0)
    {
        str[i++] = '-';
        temp = ft_itoa_len(-exponent, &len);
    }
    else
    {
        str[i++] = '+';
        temp = ft_itoa_len(exponent, &len);
    }

    len = 4; // You want 4 digits like 0003
    temp = ft_pad_string(temp, len, '0', false);
    while (j < len)
        str[i++] = temp[j++];

    str[i] = '\0'; // Null-terminate for safety if needed
    free(temp);
}

void ft_to_str_frac(t_snumb *result, char *str)
{
    int len;
    char *temp;
    int i;
    
    i = 0;
    temp = ft_itoa_len(result->fraction, &len);
    temp = ft_pad_string(temp, result->precision, '0', false);
    while ( i < result->precision)
    {
        str[i] = temp[i];
        i++;   
    }
    str[i++] = 'e';
    free(temp);
    ft_handle_exponent(&str[i], result->exponent);
}


char *ft_build_strfloat(float numb, int precision)
{
    if (isinf(numb) || isnan(numb) || numb > FLT_MAX || numb < -FLT_MAX)
        return NULL;
    t_snumb *snumb = ft_convert_to_s_number((double)numb, precision, 1);
    if (!snumb )
        return NULL;

    // Length breakdown:
    // sign (1) + whole (1) + dot (1) + precision digits + 'e' (1) + sign (1) + 4 digits (exponent) + null (1)
    int total_len = 1 + 1 + 1 + precision + 1 + 1 + 4 + 1;
    char *strfloat = malloc(total_len);
    if (!strfloat)
    {
        free(snumb);
        return NULL;
    }

    int i = 0;
    if (snumb->sign)
        strfloat[i++] = '-';

    strfloat[i++] = snumb->whole + '0';
    strfloat[i++] = '.';

    ft_to_str_frac(snumb, &strfloat[i]);
    free(snumb);

    return strfloat;
}


#include <stdio.h>

// int main(void)
// {
//     char *s;
// 	// t_snumb *s = ft_convert_to_s_number(-1.00014, 8,1);
//     s=ft_build_strfloat(-0.00012500014, 8);
//     printf("%s\n",s);
//     free(s);
// }


#include <stdio.h>
int main() {
    double test_values[] = {
        1e100,
        1e-100,
        0.0,
        1.0,
        -1.0,
        1234.56,
        -1234.56,
        0.00123,
        -0.00123,
        999999.9,
        -999999.9,
        3.1415926535,
        -3.1415926535,
        -0.1,
        1e10,
        -1e-10,
        5.0,
        -5.0,
        10.0,
        0.1
    };

    int n = sizeof(test_values) / sizeof(test_values[0]);
    for (int i = 0; i < n; i++) {
        double x = test_values[i];
        char *s;
        s=ft_build_strfloat(x,6);
        if(s)
        {
            printf("%s\n",s);
            free(s);
        }
        else
        {
            printf("not suported\n\n");
        }
        
    }

    printf("Float max: %e\n", FLT_MAX);
    printf("Float min (positive): %e\n", FLT_MIN);
    printf("Float epsilon (precision): %e\n", FLT_EPSILON);
    printf("Float max exponent: %d\n", FLT_MAX_EXP);
    printf("Float min exponent: %d\n", FLT_MIN_EXP);
    return 0;
}



