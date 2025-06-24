/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:19:28 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 17:09:52 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"
#include <stdlib.h>
typedef struct 
{
    int len;
    int curent_index;
    char *str;
} exponential;

int get_decimal_exponent(double nub)
{
    int exponent = 0;

    if (nub == 0.0)
        return 0;

    double abs_nub = (nub < 0) ? -nub : nub;

    // Normalize nub so that it is in [1, 10)
    while (abs_nub >= 10.0)
    {
        abs_nub /= 10.0;
        exponent++;
    }

    while (abs_nub > 0 && abs_nub < 1.0)
    {
        abs_nub *= 10.0;
        exponent--;
    }

    return exponent;
}


char *ft_print_exponential(double nub, int precision)
{
    char *str = NULL;
    exponential *exp;

    exp = malloc(sizeof(*exp));  // Correct allocation
    if (!exp)
        return NULL;

    exp->curent_index = 0;
    str = ft_print_double(nub, precision);
    if (!str)
    {
        free(exp);
        return NULL;
    }

    exp->str = malloc(precision + 8);  // enough for "[-]d.ddddde±dd" + null
    if (!exp->str)
    {
        free(exp);
        free(str);
        return NULL;
    }

    
    
    if (str && ((str[1]>= '0' && str[1]<= '9') || str[1]== '.'))
    {
        int n;
        int i;
        n=0;
        n=get_decimal_exponent(nub);
        printf("\nthe exponent is %d\n",n);

        i = 0;
        if (str[0] == '-')
        {
            exp->str[exp->curent_index++] = '-';
            i++;
        }
    
        // Copy the first digit
        exp->str[exp->curent_index++] = str[i++];
    
        // Add decimal point
        exp->str[exp->curent_index++] = '.';
        // Copy next digits until desired precision
        int j = 0;
        while (str[i] && str[i] != '.' && j < precision)
        {
            exp->str[exp->curent_index++] = str[i++];
            j++;
        }
    
        if (str[i] == '.')
            i++;  // skip '.'
    
        while (str[i] && j < precision)
        {
            exp->str[exp->curent_index++] = str[i++];
            j++;
        }
        // Add exponent part
        exp->str[exp->curent_index++] = 'e';
        exp->str[exp->curent_index++] = '+';
    
        // Compute exponent (based on how many digits before decimal in original str)
        
        int exp_val = 0;
        if (str[0] == '-')
            exp_val = strchr(str, '.') - str - 1;
        else
            exp_val = strchr(str, '.') - str;
    
        exp->str[exp->curent_index++] = '0' + (exp_val / 10) % 10;
        exp->str[exp->curent_index++] = '0' + (exp_val % 10-1);
        
    }
    else if (str)
    {
        while (str[exp->curent_index])
        {
            exp->str[exp->curent_index]=str[exp->curent_index];
            exp->curent_index++;
        }
    }
    exp->str[exp->curent_index] = '\0';
    free(str);
    char *result = exp->str;
    free(exp);
    return result;
}
