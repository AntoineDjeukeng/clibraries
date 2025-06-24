/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_long_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:32:40 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/23 09:02:00 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"
static void	ft_hft_print_long_double(t_number_type *number, char *result,
		int precision)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < number->intlen)
	{
		result[i] = number->intpar[i];
		i++;
	}
	if (number->decpart)
	{
		number->decpart = ft_pad_string(number->decpart, precision, '0', false);
		result[i++] = '.';
		while (j < precision)
			result[i++] = number->decpart[j++];
	}
	result[i] = '\0';

	free(number->intpar);
	if (number->decpart)
		free(number->decpart);
	free(number);
}

char	*ft_print_long_double(long double nub, int precision)
{
	t_number_type	*number;
	char			*result;
	int				len;

	// Handle rounding safely for long double
	if (nub < 0 && !(signbit(nub) && nub == 0.0))
		nub -= 5.0L / ft_power(precision + 1);
	else if (nub > 0 && !(signbit(nub) && nub == 0.0))
		nub += 5.0L / ft_power(precision + 1);

	number = ft_itoa_long_double_split(nub, precision);
	if (!number || !number->intpar)
		return (NULL);

	len = number->intlen;
	if (number->decpart)
		len += 1 + precision;

	result = malloc(len + 1);
	if (!result)
	{
		free(number->intpar);
		if (number->decpart)
			free(number->decpart);
		free(number);
		return (NULL);
	}
	ft_hft_print_long_double(number, result, precision);
	return (result);
}
