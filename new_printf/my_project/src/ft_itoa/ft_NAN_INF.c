/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_NAN_INF.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:35:09 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/19 14:03:45 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_itoa.h"
#include <math.h>

char	*handle_special_float(float n, int *len)
{
	if (isnan(n))
	{
		*len = 3;
		return (ft_strjoin("", "nan"));
	}
	if (isinf(n))
	{
		if (n < 0)
		{
			*len = 4;
			return (ft_strjoin("-", "inf"));
		}
		else
		{
			*len = 3;
			return (ft_strjoin("", "inf"));
		}
	}
	return (NULL);
}

char	*handle_special_double(double n, int *len)
{
	if (isnan(n))
	{
		*len = 3;
		return (ft_strjoin("", "nan"));
	}
	if (isinf(n))
	{
		if (n < 0)
		{
			*len = 4;
			return (ft_strjoin("-", "inf"));
		}
		else
		{
			*len = 3;
			return (ft_strjoin("", "inf"));
		}
	}
	return (NULL);
}

char	*handle_special_long_double(long double n, int *len)
{
	if (isnanl(n))
	{
		*len = 3;
		return (ft_strjoin("", "nan"));
	}
	if (n == -__builtin_infl())
	{
		*len = 4;
		return (ft_strjoin("-", "inf"));
	}
	if (n == __builtin_infl())
	{
		*len = 3;
		return (ft_strjoin("", "inf"));
	}
	return (NULL);
}
