/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken <adjeuken@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:54:20 by adjeuken          #+#    #+#             */
/*   Updated: 2025/05/21 09:53:54 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sft_strlen(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		count++;
		str++;
	}
	return (count);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	ls;
	unsigned int	temp;
	unsigned int	len;

	ls = sft_strlen(src);
	while (*dest != '\0')
		dest++;
	if (size > 0)
	{
		if (ls < size - 1)
			temp = ls;
		else
			temp = size - 1;
		while (temp > 0)
		{
			*dest = *src;
			dest++;
			src++;
			temp--;
		}
		*dest = '\0';
	}
	len = ls;
	return (len);
}
