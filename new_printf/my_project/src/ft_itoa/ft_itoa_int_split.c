/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_int_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:46:38 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 13:54:49 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_itoa.h"

static int count_int_int_digits(int n)
{
    int len = 0;

    if (n <= 0)
        len++;
    while (n)
    {
        len++;
        n /= 10;
    }
    return (len);
}

static void fill_number_digits(char *str, int n, int len)
{
    int digit;
    int pos = len;

    if (n == 0)
    {
        str[--pos] = '0';
        return;
    }
    while (n)
    {
        digit = n % 10;
        if (digit < 0)
            digit = -digit;
        str[--pos] = digit + '0';
        n /= 10;
    }
}

t_number_type *ft_itoa_int_split(int n)
{
    int len;
    t_number_type *result;
    int is_negative;

    result = malloc(sizeof(t_number_type));
    if (!result)
        return (NULL);

    is_negative = (n < 0);

    len = count_int_int_digits(n);
    result->intpar = malloc(len + 1);
    if (!result->intpar)
    {
        free(result);
        return (NULL);
    }
    result->intpar[len] = '\0';

    // Fill digits from the end, skipping the sign position if negative
    fill_number_digits(result->intpar + (is_negative ? 1 : 0), n, len - (is_negative ? 1 : 0));

    // Add sign if needed
    if (is_negative)
        result->intpar[0] = '-';

    result->decpart = NULL;  // no decimal part for int
    result->valide = 2;
    result->intlen = len;
    result->declen = 0;

    return (result);
}
