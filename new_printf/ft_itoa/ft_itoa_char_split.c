/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_char_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:54:21 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/18 18:54:28 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ito.h" // Make sure this includes the definition for t_number_type

static int	count_char_digits(char n)
{
	int	len = 0;

	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	fill_char_digits(char *str, char n, int pos)
{
	int	digit;

	if (n == 0)
	{
		str[--pos] = '0';
		return;
	}
	while (n)
	{
		digit = n % 10;
		if (digit < 0)
			digit = -digit;
		str[--pos] = digit + '0';
		n /= 10;
	}
}

t_number_type	*ft_itoa_char_split(char n)
{
	t_number_type	*result;
	int				len;

	len = count_char_digits(n);
	result = malloc(sizeof(t_number_type));
	if (!result)
		return (NULL);
	result->intpar = malloc(len + 1);
	if (!result->intpar)
	{
		free(result);
		return (NULL);
	}
	result->intpar[len] = '\0';
	if (n < 0)
		result->intpar[0] = '-';
	fill_char_digits(result->intpar, n, len);

	result->intlen = len;
	result->valide = 2;
	result->decpart = NULL;
	result->declen = 0;

	return (result);
}
