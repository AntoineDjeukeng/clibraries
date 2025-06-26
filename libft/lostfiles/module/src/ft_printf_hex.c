/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:34:59 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/24 13:35:03 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_type.h"

char	*ft_print_hex(unsigned int nub, char c)
{
	char	*number;
	char	*result;

	number = ft_itoa_hex_split(nub, c);
	if (!number)
		return (NULL);
	result = ft_strdup(number);
	free(number);
	return (result);
}
