/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_try_to_parse_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 03:02:42 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/25 10:49:42 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static int	ft_skip_whitespace_and_sign(const char *str, int *index, int *sign)
{
	*sign = 1;
	while (ft_isspace(str[*index]))
		(*index)++;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			*sign = -1;
		(*index)++;
	}
	return (1);
}

static int	ft_parse_digits(const char *str, int *index, long *result)
{
	long	temp;
	int		i;
	int		digit_count;

	temp = 0;
	i = *index;
	digit_count = 0;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (digit_count >= 10)
			return (0);
		temp = temp * 10 + (str[i] - '0');
		digit_count++;
		i++;
	}
	*result = temp;
	*index = i;
	return (1);
}

int	ft_try_parse_int(const char *str, int *out)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	if (!ft_skip_whitespace_and_sign(str, &i, &sign))
		return (0);
	if (!ft_parse_digits(str, &i, &result))
		return (0);
	if ((sign == 1 && result > INT_MAX) || (sign == -1 && - result < INT_MIN))
		return (0);
	if (str[i] != '\0')
		return (0);
	if (out)
		*out = (int)(sign * result);
	return (1);
}
