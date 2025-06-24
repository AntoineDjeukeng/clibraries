/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uchar_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:39:14 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 13:54:28 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_itoa.h"

static int	count_uchar_digits(unsigned char n)
{
	int len = 0;

	if (n == 0)
		return 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return len;
}

static void	fill_uchar_digits(char *str, unsigned char n, int pos)
{
	if (n == 0)
	{
		str[--pos] = '0';
		return;
	}
	while (n)
	{
		str[--pos] = (n % 10) + '0';
		n /= 10;
	}
}

t_number_type	*ft_itoa_uchar_split(unsigned char n)
{
	t_number_type	*result;
	int				len;

	len = count_uchar_digits(n);
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
	fill_uchar_digits(result->intpar, n, len);

	result->intlen = len;
	result->valide = 1;
	result->decpart = NULL;
	result->declen = 0;

	return result;
}
