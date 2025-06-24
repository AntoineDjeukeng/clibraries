/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:42:20 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/18 18:32:04 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ito.h"

static int	count_long_digits(long n)
{
	int	len = 0;

	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return len;
}

static void	fill_long_digits(char *str, long n, int pos)
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

t_number_type	*ft_itoa_long_split(long n)
{
	t_number_type	*result;
	int				len;

	len = count_long_digits(n);
	result = malloc(sizeof(t_number_type));
	if (!result)
		return NULL;

	result->intpar = malloc(len + 1);
	if (!result->intpar)
	{
		free(result);
		return NULL;
	}
	result->intpar[len] = '\0';

	if (n < 0)
		result->intpar[0] = '-';
	fill_long_digits(result->intpar, n, len);

	result->valide = 2;
	result->intlen = len;
	result->decpart = NULL;
	result->declen = 0;

	return result;
}
