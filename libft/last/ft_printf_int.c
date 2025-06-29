/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:51:26 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/29 16:11:47 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*build_number_str(char *num_part, int value, int prec_zeros,
		t_flags *f)
{
	char	sign_char;
	int		len;
	char	*final;
	int		i;

	sign_char = '\0';
	len = ft_strlen(num_part) + prec_zeros;
	i = 0;
	if (value < 0)
		sign_char = '-';
	else if (f->plus)
		sign_char = '+';
	else if (f->space)
		sign_char = ' ';
	if (sign_char)
		len += 1;
	final = malloc(len + 1);
	if (!final)
		return (NULL);
	if (sign_char)
		final[i++] = sign_char;
	while (prec_zeros-- > 0)
		final[i++] = '0';
	ft_strlcpy(final + i, num_part, ft_strlen(num_part) + 1);
	return (final);
}

char	*ft_print_int(t_flags *f, int value)
{
	char	*num_part;
	char	*final;
	int		prec_zeros;

	num_part = ft_itoa_int(value);
	prec_zeros = 0;
	if (!num_part)
		return (NULL);
	if (f->precision_specified && f->precision > (int)ft_strlen(num_part))
		prec_zeros = f->precision - ft_strlen(num_part);
	final = build_number_str(num_part, value, prec_zeros, f);
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
