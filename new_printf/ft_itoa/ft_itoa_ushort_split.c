/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ushort_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:52:27 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/18 18:53:11 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ito.h"

static int	count_ushort_digits(unsigned short n)
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

static void	fill_ushort_digits(char *str, unsigned short n, int pos)
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

t_number_type	*ft_itoa_ushort_split(unsigned short n)
{
	t_number_type	*result;
	int				len;

	len = count_ushort_digits(n);
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
	fill_ushort_digits(result->intpar, n, len);

	result->intlen = len;
	result->valide = 1;
	result->decpart = NULL;
	result->declen = 0;

	return result;
}

