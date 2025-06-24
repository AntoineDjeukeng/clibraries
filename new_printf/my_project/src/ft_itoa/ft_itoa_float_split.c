/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_float_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:49:13 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 17:07:05 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_itoa.h"
#include <float.h>

static float	extract_digits(float *vnumb, int *len, t_word **head)
{
	float	power;
	int		digit;

	power = 1.0;
	while (*vnumb / power >= 10.0)
		power *= 10.0;
	while (power >= 1.0)
	{
		digit = (int)(*vnumb / power);
		*vnumb -= digit * power;
		ft_add_char(head, digit + '0');
		(*len)++;
		power /= 10.0;
	}
	return (*vnumb);
}


float	ft_count_float_integer_digits(float vnumb, int *len, t_word **head)
{
	*len = 0;
	*head = NULL;
	if (vnumb < 0.0 || (signbit(vnumb) && vnumb == 0.0f))
	{
		vnumb = -vnumb;
		(*len)++;
		ft_add_char(head, '-');
	}
	if (vnumb < 1.0)
	{
		ft_add_char(head, '0');
		(*len)++;
		return (vnumb);
	}
	return (extract_digits(&vnumb, len, head));
}

static int	ft_htype(t_number_type *result, float n)
{
	int	len;

	len = 0;
	result->valide = 0;
	result->decpart = NULL;
	result->declen = 0;
	result->intpar = handle_special_float(n, &len);
	if (result->intpar)
	{
		result->intlen = len;
		result->valide = -1;
	}
	return (len);
}

t_number_type	*ft_itoa_float_split(float n, int precision)
{
	int				len;
	t_word			*digits;
	float			dec;
	t_number_type	*result;



	len = 0;
	result = malloc(sizeof(t_number_type));
	digits = NULL;
	if (!result)
		return (NULL);
	len = ft_htype(result, n);
	if (result->valide == -1)
		return (result);
	dec = ft_count_float_integer_digits(n, &len, &digits);
	result->intpar = ft_free_word(digits, len);
	result->intlen = len;
	digits = NULL;
	dec = ft_count_float_integer_digits(dec * ft_power((float)precision), &len,
			&digits);
	result->decpart = ft_free_word(digits, len);
	result->declen = len;
	return (result);
}
