/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:51:26 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/24 17:43:37 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_type.h"

char	*ft_print_int(int nub,int sign)
{
	char	*number;
	char	*result;

	if (nub<0)
		sign=1;
	number = ft_itoa_int(nub);
	if (!number)
		return (NULL);
	if(sign>=0)
		result = ft_strdup(number);
	free(number);
	return (result);
}
