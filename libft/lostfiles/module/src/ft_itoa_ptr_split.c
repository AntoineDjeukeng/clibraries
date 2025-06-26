/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ptr_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:46:38 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/24 16:06:21 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_type.h"

static int	count_unsigned_long_digits(unsigned long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

char	*ft_itoa_hex_long(unsigned long long n, char uppercase)
{
	int			len;
	const char	*base;
	char		*result;

	len = count_unsigned_long_digits(n);
	base = "0123456789abcdef";
	if (uppercase == 'X')
		base = "0123456789ABCDEF";
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len)
	{
		result[--len] = base[n % 16];
		n /= 16;
	}
	return (result);
}

char	*ft_print_pointer(void *ptr)
{
	unsigned long long	addr;
	char				*hex_str;
	size_t				total_len;
	char				*result;

	if (!ptr)
		return (NULL);
	addr = (unsigned long long)(uintptr_t)ptr;
	hex_str = ft_itoa_hex_long(addr, 'x');
	if (!hex_str)
		return (NULL);
	total_len = strlen(hex_str) + 1;
	result = malloc(total_len);
	if (!result)
	{
		free(hex_str);
		return (NULL);
	}
	free(hex_str);
	return (result);
}
