/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long_long_split.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:43:55 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 13:54:40 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_itoa.h"

static int	count_ll_digits(long long n)
{
	int	len = 0;

	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return len;
}

static void	fill_ll_digits(char *str, long long n, int pos)
{
	int digit;

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

t_number_type	*ft_itoa_long_long_split(long long n)
{
	t_number_type	*result;
	int				len;

	len = count_ll_digits(n);
	result = malloc(sizeof(t_number_type));
	if (!result)
		return (NULL);
	result->intpar = malloc(len + 1);
	if (!result->intpar)
	{
		free(result);
		return (NULL);
	}
	result->intpar[len] = '\0';
	if (n < 0)
		result->intpar[0] = '-';
	fill_ll_digits(result->intpar, n, len);
	result->valide = 2;
	result->intlen = len;
	result->decpart = NULL;
	result->declen = 0;
	return result;
}
