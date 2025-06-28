/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:34:59 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/28 20:35:01 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prinf.h"

static char	*ft_flag_h(t_flags *f, char *num_part, int prec_zeros,
		unsigned int value)
{
	int		i;
	char	*final;

	i = 0;
	final = malloc(ft_strlen(num_part) + prec_zeros + 1);
	if (!final)
		return (NULL);
	while (prec_zeros-- > 0)
		final[i++] = '0';
	ft_strlcpy(final + i, num_part, ft_strlen(num_part) + 1);
	if (f->hash)
	{
		if (value != 0)
		{
			if (f->specifier == 'x')
				final = ft_pad_string(final, ft_strlen(final) + 1, 'x',
						f->minus);
			else
				final = ft_pad_string(final, ft_strlen(final) + 1, 'X',
						f->minus);
			final = ft_pad_string(final, ft_strlen(final) + 1, '0', f->minus);
		}
	}
	return (final);
}

char	*ft_print_hex(t_flags *f, unsigned int value)
{
	char	*num_part;
	char	*final;
	int		prec_zeros;
	int		len;

	prec_zeros = 0;
	num_part = ft_itoa_hex_split(value, f->specifier);
	if (!num_part)
		return (NULL);
	len = ft_strlen(num_part);
	if (f->precision_specified && f->precision > len)
		prec_zeros = f->precision - len;
	final = ft_flag_h(f, num_part, prec_zeros, value);
	free(num_part);
	if (!final)
		return (NULL);
	if (f->width > (int)ft_strlen(final))
	{
		if (f->zero && !f->precision_specified && !f->minus)
			final = ft_pad_string(final, f->width, '0', f->minus);
		else
			final = ft_pad_string(final, f->width, ' ', f->minus);
	}
	return (final);
}
