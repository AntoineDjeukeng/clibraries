/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:55:06 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/22 14:45:01 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(int nb, char *str, int *p)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		str[(*p)++] = '-';
		n = -n;
	}
	if (n >= 10)
		ft_putnbr(n / 10, str, p);
	str[(*p)++] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		pos;

	pos = 0;
	str = malloc(21);
	if (!str)
		return (NULL);
	ft_putnbr(n, str, &pos);
	str[pos] = '\0';
	return (str);
}
