/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 08:09:53 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/07 16:09:32 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_valid_base(const char *base)
{
	int	len;
	int	i;
	int	j;

	if (!base)
		return (0);
	len = ft_strlen(base);
	if (len < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ' || (base[i] >= 9
				&& base[i] <= 13))
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

char	*utoa_base_str(unsigned int n, int is_negative, const char *base,
		int *length)
{
	char	*res;
	int		base_len;
	int		i;

	base_len = ft_strlen(base);
	res = malloc(*length + 1);
	if (!res)
		return (NULL);
	res[*length] = '\0';
	i = *length - 1;
	while (i >= is_negative)
	{
		res[i--] = base[n % base_len];
		n /= base_len;
	}
	if (is_negative)
		res[0] = '-';
	return (res);
}

char *ft_itoa_base_unsigned(unsigned int num, const char *base, int *length)
{
	int base_len = ft_strlen(base);
	int digits = 1;
	unsigned int tmp = num;

	if (!is_valid_base(base))
		return NULL;

	while (tmp >= (unsigned int)base_len)
	{
		tmp /= base_len;
		digits++;
	}

	*length = digits;
	return utoa_base_str(num, 0, base, length);
}

char	*ft_itoa_base(int n, const char *base, int *length)
{
	int				is_negative;
	unsigned int	num;
	int				base_len;
	int				digits;
	unsigned int	tmp;

	if (!is_valid_base(base))
		return (NULL);
	is_negative = (n < 0);
	if (is_negative)
		num = (unsigned int)(-(long)n);
	else
		num = (unsigned int)n;
	base_len = ft_strlen(base);
	digits = 1;
	{
		tmp = num;
		while (tmp >= (unsigned int)base_len)
		{
			tmp /= base_len;
			digits++;
		}
	}
	*length = digits + is_negative;
	return (utoa_base_str(num, is_negative, base, length));
}

