/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:34:44 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/29 16:12:14 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_flag_u(t_flags *f, char *num_part, int prec_zeros, int total_len)
{
	int		i;
	char	*final;

	i = 0;
	final = malloc(total_len + 1);
	if (!final)
	{
		free(num_part);
		return (NULL);
	}
	while (prec_zeros-- > 0)
		final[i++] = '0';
	ft_strlcpy(final + i, num_part, ft_strlen(num_part) + 1);
	free(num_part);
	if (f->width > total_len)
	{
		if (f->zero && !f->precision_specified && !f->minus)
			final = ft_pad_string(final, f->width, '0', f->minus);
		else
			final = ft_pad_string(final, f->width, ' ', f->minus);
	}
	return (final);
}

char	*ft_print_uint(t_flags *f, unsigned int value)
{
	char	*num_part;
	int		prec_zeros;
	int		len;

	prec_zeros = 0;
	num_part = ft_itoa_uint_split(value);
	if (!num_part)
		return (NULL);
	len = ft_strlen(num_part);
	if (f->precision_specified && f->precision > len)
		prec_zeros = f->precision - len;
	return (ft_flag_u(f, num_part, prec_zeros, len + prec_zeros));
}
