/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:16:20 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 13:53:56 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_itoa.h"

void	simple_modf_double(double num, double *intpart, double *fracpart)
{
	int	sign;

	sign = 1;
	*intpart = 0.0;
	if (num < 0)
	{
		sign = -1;
		num = -num;
	}
	while (num >= 1.0)
	{
		*intpart += 1.0;
		num -= 1.0;
	}
	*intpart *= sign;
	*fracpart = num * sign;
}

void	simple_modf_float(float num, float *intpart, float *fracpart)
{
	int	sign;

	sign = 1;
	*intpart = 0.0f;
	if (num < 0.0f)
	{
		sign = -1;
		num = -num;
	}
	while (num >= 1.0f)
	{
		*intpart += 1.0f;
		num -= 1.0f;
	}
	*intpart *= sign;
	*fracpart = num * sign;
}

void	simple_modf_long_double(long double num, long double *intpart,
		long double *fracpart)
{
	int	sign;

	sign = 1;
	*intpart = 0.0L;
	if (num < 0.0L)
	{
		sign = -1;
		num = -num;
	}
	while (num >= 1.0L)
	{
		*intpart += 1.0L;
		num -= 1.0L;
	}
	*intpart *= sign;
	*fracpart = num * sign;
}
