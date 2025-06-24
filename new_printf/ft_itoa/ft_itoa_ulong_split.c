/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ulong_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:53:07 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/18 18:43:48 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ito.h"

static int	count_ul_digits(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

t_number_type	*ft_itoa_ulong_split(unsigned long n)
{
	int				len;
	t_number_type	*result;

	len = count_ul_digits(n);
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
	result->intlen = len;
	result->valide = 1;
	result->decpart = NULL;
	result->declen = 0;
	while (len)
	{
		result->intpar[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
