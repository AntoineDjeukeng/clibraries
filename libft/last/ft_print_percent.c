/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:07:03 by adjeuken          #+#    #+#             */
/*   Updated: 2025/06/28 20:32:59 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prinf.h"

char	*ft_flag_percent(t_flags *f)
{
	char	*result;

	result = malloc(2);
	if (!result)
		return (NULL);
	result[0] = '%';
	result[1] = '\0';
	if (f->width > 1)
	{
		if (f->zero && !f->minus)
			result = ft_pad_string(result, f->width, '0', f->minus);
		else
			result = ft_pad_string(result, f->width, ' ', f->minus);
	}
	return (result);
}
