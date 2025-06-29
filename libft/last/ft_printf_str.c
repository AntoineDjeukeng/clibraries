/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:18:57 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/29 16:12:07 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_handel_c(char value)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = (char)(uintptr_t)value;
	str[1] = '\0';
	return (str);
}

char	*ft_format_str_or_char(t_flags *f, void *value)
{
	char	*str;
	char	*s;

	if (f->specifier == 'c')
		str = ft_handel_c((char)(uintptr_t)value);
	else if (f->specifier == 's')
	{
		s = (char *)value;
		if (!s)
			return (ft_strdup("(null)"));
		if (f->precision_specified)
			str = ft_substr(s, 0, f->precision);
		else
			str = ft_strdup(s);
		if (!str)
			return (NULL);
	}
	else
		return (NULL);
	if (f->width > (int)strlen(str))
		str = ft_pad_string(str, f->width, ' ', f->minus);
	return (str);
}
