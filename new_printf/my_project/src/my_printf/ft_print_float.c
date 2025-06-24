/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:19:28 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 17:28:50 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_printf.h"

static void	ft_hft_print_float(t_number_type *number, char *result,
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

char	*ft_print_float(float nub, int precision)
{
	t_number_type	*number;
	char			*result;
	int				len;
    
	if (nub < 0 && !((signbit(nub) && nub == 0.0f)) )
		nub = nub - 5.0f / ft_power(precision + 1);
	if (nub > 0 && !((signbit(nub) && nub == 0.0f)) )
		nub = nub + 5.0f / ft_power(precision + 1);
	number = ft_itoa_float_split(nub, precision);
	if (!number || !number->intpar)
		return (NULL);
	len = number->intlen;
	if (number->decpart)
		len = number->intlen + 1 + precision;
	result = malloc(len + 1);
	if (!result)
	{
		free(number->intpar);
		if (number->decpart)
			free(number->decpart);
		free(number);
		return (NULL);
	}
	ft_hft_print_float(number, result, precision);
	return (result);
}
