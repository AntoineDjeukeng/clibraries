/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:34:44 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/24 13:34:46 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_type.h"

char	*ft_print_uint(unsigned int nub)
{
	char	*number;
	char	*result;

	number = ft_itoa_uint_split(nub);
	if (!number)
		return (NULL);
	result = ft_strdup(number);
	free(number);
	return (result);
}
